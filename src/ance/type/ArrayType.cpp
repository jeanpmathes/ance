#include "ArrayType.h"

#include "ance/construct/value/Value.h"
#include "ance/construct/value/WrappedNativeValue.h"
#include "ance/scope/GlobalScope.h"
#include "ance/type/ReferenceType.h"
#include "ance/type/SizeType.h"
#include "ance/utility/Values.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

ance::ArrayType::ArrayType(Application& app, Type* element_type, const uint64_t size)
    : size_(size)
    , element_type_(element_type)
    , element_reference_(ance::ReferenceType::get(app, element_type))
{}

std::string ance::ArrayType::getName()
{
    return "[" + element_type_->getName() + "; " + std::to_string(size_) + "]";
}

llvm::Constant* ance::ArrayType::getDefaultContent(llvm::LLVMContext& c)
{
    std::vector<llvm::Constant*> content(size_, element_type_->getDefaultContent(c));
    return llvm::ConstantArray::get(type_, content);
}

llvm::Type* ance::ArrayType::getContentType(llvm::LLVMContext& c)
{
    if (!type_) { type_ = llvm::ArrayType::get(element_type_->getContentType(c), size_); }

    return type_;
}

bool ance::ArrayType::validate(ValidationLogger& validation_logger, ance::Location location)
{
    if (ance::ReferenceType::isReferenceType(element_type_))
    {
        validation_logger.logError("Cannot declare arrays of reference types", location);
        return false;
    }

    return true;
}

bool ance::ArrayType::isIndexerDefined()
{
    return true;
}

ance::Type* ance::ArrayType::getIndexerReturnType()
{
    return element_reference_;
}

bool ance::ArrayType::validateGetIndexer(ance::Value* indexed,
                                         ance::Location,
                                         ance::Value*      index,
                                         ance::Location    index_location,
                                         ValidationLogger& validation_logger)
{
    assert(indexed->type() == this && "Method call on wrong type.");

    return checkMismatch(ance::SizeType::getSize(), index->type(), index_location, validation_logger);
}

ance::Value* ance::ArrayType::buildGetIndexer(ance::Value* indexed, ance::Value* index, CompileContext* context)
{
    index = ance::Type::makeMatching(ance::SizeType::getSize(), index, context);

    llvm::Value* element_ptr  = buildGetElementPointer(indexed, index, context);
    llvm::Value* native_value = ance::Values::contentToNative(element_reference_, element_ptr, context);

    return new ance::WrappedNativeValue(getIndexerReturnType(), native_value);
}

llvm::Value* ance::ArrayType::buildGetElementPointer(ance::Value*    indexed,
                                                     ance::Value*    index,
                                                     CompileContext* context) const
{
    indexed->buildNativeValue(context);
    index->buildContentValue(context);

    llvm::Value* zero         = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context->llvmContext()), 0);
    llvm::Value* native_index = index->getContentValue();
    llvm::Value* indices[]    = {zero, native_index};

    llvm::Value* array_ptr =
        indexed->getNativeValue();// This is a pointer as the internal storage of arrays is using pointers.

    // Check if index is smaller than size.
    llvm::Value* native_size =
        llvm::ConstantInt::get(ance::SizeType::getSize()->getContentType(*context->llvmContext()), size_);
    llvm::Value* in_bounds = context->ir()->CreateICmpULT(native_index, native_size);

    in_bounds->setName("..inbounds");

    // todo: use in_bounds bool to throw exception

    llvm::Value* element_ptr = context->ir()->CreateGEP(array_ptr, indices);
    return element_ptr;
}

llvm::DIType* ance::ArrayType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl         = context->module()->getDataLayout();
    llvm::Type*             array_type = getContentType(*context->llvmContext());

    uint64_t      size            = dl.getTypeSizeInBits(array_type) / 8;
    uint32_t      alignment       = dl.getABITypeAlignment(array_type);
    llvm::DIType* element_di_type = element_type_->getDebugType(context);

    llvm::SmallVector<llvm::Metadata*, 1> subscripts;
    subscripts.push_back(context->di()->getOrCreateSubrange(0, (int64_t) size_));

    return context->di()->createArrayType(size,
                                          alignment,
                                          element_di_type,
                                          context->di()->getOrCreateArray(subscripts));
}

ance::Type* ance::ArrayType::get(Application& app, Type* element_type, uint64_t size)
{
    auto*       type      = new ance::ArrayType(app, element_type, size);
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
