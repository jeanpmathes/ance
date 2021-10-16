#include "PointerType.h"

#include "ance/construct/value/Value.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/scope/GlobalScope.h"
#include "ance/type/ReferenceType.h"
#include "ance/type/SizeType.h"
#include "ance/type/VoidType.h"
#include "ance/utility/Values.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::PointerType::PointerType(ance::Type* element_type)
    : Type("*" + element_type->getName())
    , element_type_(element_type)
    , element_reference_(ance::ReferenceType::get(element_type))
{}

llvm::Constant* ance::PointerType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantPointerNull::get(getContentType(c));
}

llvm::PointerType* ance::PointerType::getContentType(llvm::LLVMContext& c)
{
    llvm::Type* native_type;

    if (element_type_ == ance::VoidType::get()) { native_type = llvm::Type::getInt8PtrTy(c); }
    else
    {
        native_type = element_type_->getContentType(c);
    }

    return llvm::PointerType::get(native_type, 0);
}

bool ance::PointerType::validate(ValidationLogger& validation_logger, ance::Location location)
{
    if (ance::ReferenceType::isReferenceType(element_type_))
    {
        validation_logger.logError("Cannot declare pointers to reference types", location);
        return false;
    }

    return true;
}

bool ance::PointerType::isSubscriptDefined()
{
    return true;
}

ance::Type* ance::PointerType::getSubscriptReturnType()
{
    return element_reference_;
}

bool ance::PointerType::validateSubscript(Type* indexed_type,
                                          ance::Location,
                                          Type*             index_type,
                                          ance::Location    index_location,
                                          ValidationLogger& validation_logger)
{
    assert(indexed_type == this && "Method call on wrong type.");

    return checkMismatch(ance::SizeType::getSize(), index_type, index_location, validation_logger);
}

ance::Value* ance::PointerType::buildSubscript(ance::Value* indexed, ance::Value* index, CompileContext* context)
{
    index = ance::Type::makeMatching(ance::SizeType::getSize(), index, context);

    llvm::Value* element_ptr  = buildGetElementPointer(indexed, index, context);
    llvm::Value* native_value = ance::Values::contentToNative(element_reference_, element_ptr, context);

    return new ance::WrappedNativeValue(getSubscriptReturnType(), native_value);
}

llvm::Value* ance::PointerType::buildGetElementPointer(ance::Value*    indexed,
                                                       ance::Value*    index,
                                                       CompileContext* context)
{
    indexed->buildContentValue(context);
    index->buildContentValue(context);

    llvm::Value* native_index = index->getContentValue();
    llvm::Value* indices[]    = {native_index};

    llvm::Value* ptr = indexed->getContentValue();//Pointer to content is instead of pointer to pointer is required.

    llvm::Value* element_ptr = context->ir()->CreateGEP(ptr, indices);
    return element_ptr;
}

llvm::DIType* ance::PointerType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    uint64_t size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));

    llvm::DIType* di_type;

    if (element_type_ == ance::VoidType::get())
    {
        std::string name     = getName();
        auto        encoding = llvm::dwarf::DW_ATE_address;

        di_type = context->di()->createBasicType(name, size_in_bits, encoding);
    }
    else
    {
        llvm::DIType* element_di_type = element_type_->getDebugType(context);

        di_type = context->di()->createPointerType(element_di_type, size_in_bits);
    }

    return di_type;
}

std::map<ance::Type*, ance::PointerType*>& ance::PointerType::getPointerTypes()
{
    static std::map<ance::Type*, ance::PointerType*> pointer_types;
    return pointer_types;
}

ance::Type* ance::PointerType::get(ance::Type* element_type)
{
    auto               it           = getPointerTypes().find(element_type);
    ance::PointerType* pointer_type = nullptr;

    if (it == getPointerTypes().end())
    {
        pointer_type = new ance::PointerType(element_type);
        getPointerTypes().insert(std::make_pair(element_type, pointer_type));
    }
    else
    {
        pointer_type = it->second;
    }

    return pointer_type;
}

bool ance::PointerType::isPointerType(ance::Type* type)
{
    ance::Type* ptr_type = dynamic_cast<ance::PointerType*>(type);
    return ptr_type != nullptr;
}

ance::Type* ance::PointerType::getPointeeType(ance::Type* type)
{
    auto ptr_type = dynamic_cast<ance::PointerType*>(type);
    return ptr_type ? ptr_type->element_type_ : nullptr;
}
