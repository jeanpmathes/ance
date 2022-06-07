#include "ArrayType.h"

#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/SizeType.h"
#include "lang/utility/Values.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

lang::ArrayType::ArrayType(lang::ResolvingHandle<lang::Type> element_type, const uint64_t size)
    : TypeDefinition("[" + element_type->getName() + "; " + std::to_string(size) + "]")
    , size_(size)
    , element_type_(element_type)
    , element_reference_(lang::ReferenceType::get(element_type))
{}

StateCount lang::ArrayType::getStateCount() const
{
    StateCount state_count = element_type_->getStateCount();

    if (auto* size = std::get_if<size_t>(&state_count)) { *size *= size_; }

    return state_count;
}

lang::ResolvingHandle<lang::Type> lang::ArrayType::getElementType() const
{
    return element_type_;
}

lang::ResolvingHandle<lang::Type> lang::ArrayType::getActualType() const
{
    lang::ResolvingHandle<lang::Type> actual_element_type = element_type_->getActualType();
    if (actual_element_type == element_type_) { return self(); }
    else {
        return lang::ArrayType::get(actual_element_type, size_);
    }
}

llvm::Constant* lang::ArrayType::getDefaultContent(llvm::LLVMContext& c)
{
    std::vector<llvm::Constant*> content(size_, element_type_->getDefaultContent(c));
    return llvm::ConstantArray::get(getContentType(c), content);
}

llvm::ArrayType* lang::ArrayType::getContentType(llvm::LLVMContext& c)
{
    if (!type_) { type_ = llvm::ArrayType::get(element_type_->getContentType(c), size_); }

    return type_;
}

bool lang::ArrayType::validate(ValidationLogger& validation_logger, lang::Location location)
{
    if (size_ > MAX_ARRAY_TYPE_SIZE)
    {
        validation_logger.logError("Integer type size cannot be larger than " + std::to_string(MAX_ARRAY_TYPE_SIZE),
                                   location);
        return false;
    }

    if (!element_type_->isDefined())
    {
        validation_logger.logError("Cannot declare array of undefined type " + element_type_->getAnnotatedName(),
                                   location);
        return false;
    }

    if (element_type_->isReferenceType())
    {
        validation_logger.logError("Cannot declare arrays of reference types", location);
        return false;
    }

    return true;
}

bool lang::ArrayType::isSubscriptDefined()
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::ArrayType::getSubscriptReturnType()
{
    return element_reference_;
}

bool lang::ArrayType::validateSubscript(lang::Location,
                                        lang::ResolvingHandle<lang::Type> index_type,
                                        lang::Location                    index_location,
                                        ValidationLogger&                 validation_logger)
{
    return lang::Type::checkMismatch(lang::SizeType::getSize(), index_type, index_location, validation_logger);
}

std::shared_ptr<lang::Value> lang::ArrayType::buildSubscript(std::shared_ptr<Value> indexed,
                                                             std::shared_ptr<Value> index,
                                                             CompileContext*        context)
{
    index = lang::Type::makeMatching(lang::SizeType::getSize(), index, context);

    llvm::Value* element_ptr  = buildGetElementPointer(indexed, index, context);
    llvm::Value* native_value = lang::Values::contentToNative(element_reference_, element_ptr, context);

    return std::make_shared<lang::WrappedNativeValue>(getSubscriptReturnType(), native_value);
}

llvm::Value* lang::ArrayType::buildGetElementPointer(const std::shared_ptr<lang::Value>& indexed,
                                                     const std::shared_ptr<lang::Value>& index,
                                                     CompileContext*                     context)
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
        llvm::ConstantInt::get(lang::SizeType::getSize()->getContentType(*context->llvmContext()), size_);
    llvm::Value* in_bounds = context->ir()->CreateICmpULT(native_index, native_size, native_index->getName() + ".icmp");

    in_bounds->setName("..inbounds");

    // todo: use in_bounds bool to throw exception

    llvm::Value* element_ptr = context->ir()->CreateGEP(getContentType(*context->llvmContext()),
                                                        array_ptr,
                                                        indices,
                                                        array_ptr->getName() + ".gep");
    return element_ptr;
}

std::string lang::ArrayType::createMangledName()
{
    return std::string("(") + element_type_->getMangledName() + ")x(" + std::to_string(size_) + std::string(")");
}

llvm::DIType* lang::ArrayType::createDebugType(CompileContext* context)
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

lang::TypeRegistry<uint64_t>& lang::ArrayType::getArrayTypes()
{
    static lang::TypeRegistry<uint64_t> array_types;
    return array_types;
}

lang::TypeDefinitionRegistry* lang::ArrayType::getRegistry()
{
    return &getArrayTypes();
}

lang::ResolvingHandle<lang::Type> lang::ArrayType::get(lang::ResolvingHandle<lang::Type> element_type, uint64_t size)
{
    std::vector<lang::ResolvingHandle<lang::Type>> used_types;
    used_types.push_back(element_type);

    std::optional<lang::ResolvingHandle<lang::Type>> defined_type = getArrayTypes().get(used_types, size);

    if (defined_type.has_value()) { return defined_type.value(); }
    else {
        auto*                             array_type = new lang::ArrayType(element_type, size);
        lang::ResolvingHandle<lang::Type> type =
            lang::makeHandled<lang::Type>(std::unique_ptr<lang::ArrayType>(array_type));
        getArrayTypes().add(std::move(used_types), size, type);

        return type;
    }
}
