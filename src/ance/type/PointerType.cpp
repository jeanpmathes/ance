#include "PointerType.h"

#include "ance/construct/value/Value.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/scope/GlobalScope.h"
#include "ance/type/SizeType.h"
#include "ance/type/VoidType.h"
#include "ance/utility/Values.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"

ance::PointerType::PointerType(ance::Type* element_type) : element_type_(element_type) {}

std::string ance::PointerType::getName()
{
    return element_type_->getName() + "*";
}

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

bool ance::PointerType::isIndexerDefined(Indexer)
{
    return true;
}

ance::Type* ance::PointerType::getIndexerReturnType()
{
    return element_type_;
}

void ance::PointerType::validateGetIndexer(ance::Value* indexed, ance::Value* index, ValidationLogger&)
{
    assert(indexed->type() == this && "Indexed value has to be of pointer type.");
    assert(index->type() == ance::SizeType::get() && "Pointer index has to be size type.");
}

ance::Value* ance::PointerType::buildGetIndexer(ance::Value* indexed, ance::Value* index, CompileContext* context)
{
    llvm::Value* element_ptr    = buildGetElementPointer(indexed, index, context);
    llvm::Value* native_content = context->ir()->CreateLoad(element_ptr);

    llvm::Value* native_value = ance::Values::contentToNative(element_type_, native_content, context);
    return new ance::WrappedNativeValue(getIndexerReturnType(), native_value);
}

void ance::PointerType::validateSetIndexer(ance::Value* indexed,
                                           ance::Value* index,
                                           ance::Value* value,
                                           ValidationLogger&)
{
    assert(indexed->type() == this && "Indexed value has to be of pointer type.");
    assert(index->type() == ance::SizeType::get() && "Pointer index has to be size type.");
    assert(value->type() == element_type_ && "Assigned value has to be of element type.");
}

void ance::PointerType::buildSetIndexer(ance::Value*    indexed,
                                        ance::Value*    index,
                                        ance::Value*    value,
                                        CompileContext* context)
{
    value->buildContentValue(context);

    llvm::Value* element_ptr         = buildGetElementPointer(indexed, index, context);
    llvm::Value* new_element_content = value->getContentValue();

    context->ir()->CreateStore(new_element_content, element_ptr);
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

ance::Type* ance::PointerType::get(Application& app, ance::Type* element_type)
{
    auto*       type      = new ance::PointerType(element_type);
    std::string type_name = type->getName();

    if (app.globalScope()->isTypeRegistered(type_name))
    {
        delete type;
        return app.globalScope()->getType(type_name);
    }
    else
    {
        app.globalScope()->registerType(type);
        return type;
    }
}

bool ance::PointerType::isPointerType(ance::Type* type)
{
    ance::Type* ptr_type = dynamic_cast<ance::PointerType*>(type);
    return ptr_type != nullptr;
}
