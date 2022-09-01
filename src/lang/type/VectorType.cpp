#include "VectorType.h"

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/SizeType.h"
#include "lang/type/VectorizableType.h"
#include "lang/utility/Values.h"
#include "validation/ValidationLogger.h"

lang::VectorType::VectorType(lang::ResolvingHandle<lang::Type> element_type, uint64_t size)
    : TypeDefinition(lang::Identifier::from("<" + element_type->name() + "; " + std::to_string(size) + ">"))
    , size_(size)
    , element_type_(element_type)
    , element_reference_(lang::ReferenceType::get(element_type))
{}

const lang::VectorType* lang::VectorType::isVectorType() const
{
    return this;
}

StateCount lang::VectorType::getStateCount() const
{
    StateCount state_count = element_type_->getStateCount();

    if (auto* size = std::get_if<size_t>(&state_count)) { *size *= size_; }

    return state_count;
}

lang::ResolvingHandle<lang::Type> lang::VectorType::getElementType() const
{
    return element_type_;
}

lang::ResolvingHandle<lang::Type> lang::VectorType::getActualType() const
{
    lang::ResolvingHandle<lang::Type> actual_element_type = element_type_->getActualType();
    if (actual_element_type == element_type_) { return self(); }
    else { return lang::VectorType::get(actual_element_type, size_); }
}

llvm::Constant* lang::VectorType::getDefaultContent(llvm::Module& m)
{
    std::vector<llvm::Constant*> content(size_, element_type_->getDefaultContent(m));
    return llvm::ConstantVector::get(content);
}

llvm::Type* lang::VectorType::getContentType(llvm::LLVMContext& c) const
{
    llvm::Type* content_type;

    if (element_type_->isVectorizable())
    {
        content_type = llvm::FixedVectorType::get(element_type_->getContentType(c), size_);
    }
    else { content_type = llvm::ArrayType::get(element_type_->getContentType(c), size_); }

    return content_type;
}

bool lang::VectorType::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    if (size_ > MAX_VECTOR_TYPE_SIZE)
    {
        validation_logger.logError("Vector type size cannot be larger than " + std::to_string(MAX_VECTOR_TYPE_SIZE),
                                   location);
        return false;
    }

    if (size_ == 0)
    {
        validation_logger.logError("Vector type size cannot be zero", location);
        return false;
    }

    if (!element_type_->isDefined())
    {
        validation_logger.logError("Cannot declare vector of undefined type " + element_type_->getAnnotatedName(),
                                   location);
        return false;
    }

    if (element_type_->isReferenceType())
    {
        validation_logger.logError("Cannot declare vector of reference types", location);
        return false;
    }

    return true;
}

bool lang::VectorType::isSubscriptDefined()
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::VectorType::getSubscriptReturnType()
{
    return element_reference_;
}

bool lang::VectorType::validateSubscript(lang::Location,
                                         lang::ResolvingHandle<lang::Type> index_type,
                                         lang::Location                    index_location,
                                         ValidationLogger&                 validation_logger) const
{
    return lang::Type::checkMismatch(lang::SizeType::getSize(), index_type, index_location, validation_logger);
}

std::shared_ptr<lang::Value> lang::VectorType::buildSubscript(std::shared_ptr<Value> indexed,
                                                              std::shared_ptr<Value> index,
                                                              CompileContext&        context)
{
    index = lang::Type::makeMatching(lang::SizeType::getSize(), index, context);

    llvm::Value* element_ptr  = buildGetElementPointer(indexed, index, context);
    llvm::Value* native_value = lang::Values::contentToNative(getSubscriptReturnType(), element_ptr, context);

    return std::make_shared<lang::WrappedNativeValue>(getSubscriptReturnType(), native_value);
}

bool lang::VectorType::isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type> other)
{
    if (auto other_as_vector = other->isVectorType())
    {
        if (other_as_vector->size_ != this->size_) return false;

        other = other->getElementType();
        return element_type_->isImplicitlyConvertibleTo(other);
    }

    return false;
}

bool lang::VectorType::validateImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                  lang::Location                    location,
                                                  ValidationLogger&                 validation_logger) const
{
    return element_type_->validateImplicitConversion(other->getElementType(), location, validation_logger);
}

std::shared_ptr<lang::Value> lang::VectorType::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                       std::shared_ptr<Value>            value,
                                                                       CompileContext&                   context)
{
    if (auto element_vector = element_type_->isVectorizable())
    {
        return element_vector->buildImplicitConversion(other, other->getElementType(), value, context);
    }
    else
    {
        llvm::Value* result_ptr =
            context.ir()->CreateAlloca(other->getContentType(*context.llvmContext()), nullptr, "alloca");

        for (uint64_t index = 0; index < size_; index++)
        {
            llvm::Constant* index_content =
                llvm::ConstantInt::get(lang::SizeType::getSize()->getContentType(*context.llvmContext()), index);

            auto index_value = [&]() {
                llvm::Value* index_native =
                    lang::Values::contentToNative(lang::SizeType::getSize(), index_content, context);
                return std::make_shared<lang::WrappedNativeValue>(lang::SizeType::getSize(), index_native);
            };

            auto current_element =
                lang::Type::getValueOrReferencedValue(buildSubscript(value, index_value(), context), context);

            auto result_element =
                element_type_->buildImplicitConversion(other->getElementType(), current_element, context);
            result_element->buildContentValue(context);

            llvm::Value* result_dst_ptr = buildGetElementPointer(result_ptr, index, context);
            context.ir()->CreateStore(result_element->getContentValue(), result_dst_ptr);
        }

        return std::make_shared<lang::WrappedNativeValue>(other, result_ptr);
    }
}

bool lang::VectorType::isOperatorDefined(lang::BinaryOperator op, lang::ResolvingHandle<lang::Type> other)
{
    if (auto other_as_vector = other->isVectorType())
    {
        if (other_as_vector->size_ != this->size_) return false;

        other = other->getElementType();
        return getElementType()->isOperatorDefined(op, other);
    }

    return false;
}

lang::ResolvingHandle<lang::Type> lang::VectorType::getOperatorResultType(lang::BinaryOperator              op,
                                                                          lang::ResolvingHandle<lang::Type> other)
{
    return get(element_type_->getOperatorResultType(op, other), size_);
}

bool lang::VectorType::validateOperator(lang::BinaryOperator              op,
                                        lang::ResolvingHandle<lang::Type> other,
                                        lang::Location                    left_location,
                                        lang::Location                    right_location,
                                        ValidationLogger&                 validation_logger) const
{
    return element_type_->validateOperator(op, other, left_location, right_location, validation_logger);
}

std::shared_ptr<lang::Value> lang::VectorType::buildOperator(lang::BinaryOperator   op,
                                                             std::shared_ptr<Value> left,
                                                             std::shared_ptr<Value> right,
                                                             CompileContext&        context)
{
    if (auto element_vector = element_type_->isVectorizable())
    {
        return element_vector->buildOperator(op, left, right, getOperatorResultType(op, right->type()), context);
    }
    else
    {
        llvm::Value* result_ptr =
            context.ir()->CreateAlloca(getOperatorResultType(op, right->type())->getContentType(*context.llvmContext()),
                                       nullptr,
                                       "alloca");

        for (uint64_t index = 0; index < size_; index++)
        {
            llvm::Constant* index_content =
                llvm::ConstantInt::get(lang::SizeType::getSize()->getContentType(*context.llvmContext()), index);

            auto index_value = [&]() {
                llvm::Value* index_native =
                    lang::Values::contentToNative(lang::SizeType::getSize(), index_content, context);
                return std::make_shared<lang::WrappedNativeValue>(lang::SizeType::getSize(), index_native);
            };

            auto left_element =
                lang::Type::getValueOrReferencedValue(buildSubscript(left, index_value(), context), context);
            auto right_element =
                lang::Type::getValueOrReferencedValue(buildSubscript(right, index_value(), context), context);

            auto result_element = element_type_->buildOperator(op, left_element, right_element, context);
            result_element->buildContentValue(context);

            llvm::Value* result_dst_ptr = buildGetElementPointer(result_ptr, index, context);
            context.ir()->CreateStore(result_element->getContentValue(), result_dst_ptr);
        }

        return std::make_shared<lang::WrappedNativeValue>(getOperatorResultType(op, right->type()), result_ptr);
    }
}

llvm::Value* lang::VectorType::buildGetElementPointer(const std::shared_ptr<lang::Value>& indexed,
                                                      const std::shared_ptr<lang::Value>& index,
                                                      CompileContext&                     context) const
{
    indexed->buildNativeValue(context);
    index->buildContentValue(context);

    llvm::Value* zero         = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context.llvmContext()), 0);
    llvm::Value* native_index = index->getContentValue();
    llvm::Value* indices[]    = {zero, native_index};

    llvm::Value* vector_ptr =
        indexed->getNativeValue();// This is a pointer as the internal storage of vectors is using pointers.

    // Check if index is smaller than size.
    llvm::Value* native_size =
        llvm::ConstantInt::get(lang::SizeType::getSize()->getContentType(*context.llvmContext()), size_);
    llvm::Value* in_bounds = context.ir()->CreateICmpULT(native_index, native_size, native_index->getName() + ".icmp");

    in_bounds->setName("..inbounds");

    // todo: use in_bounds bool to throw exception

    llvm::Value* element_ptr = context.ir()->CreateGEP(getContentType(*context.llvmContext()),
                                                       vector_ptr,
                                                       indices,
                                                       vector_ptr->getName() + ".gep");
    return element_ptr;
}

llvm::Value* lang::VectorType::buildGetElementPointer(llvm::Value*    indexed,
                                                      uint64_t        index,
                                                      CompileContext& context) const
{
    llvm::Value* zero         = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context.llvmContext()), 0);
    llvm::Value* native_index = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context.llvmContext()), index);

    return context.ir()->CreateGEP(getContentType(*context.llvmContext()),
                                   indexed,
                                   {zero, native_index},
                                   indexed->getName() + ".gep");
}

void lang::VectorType::buildSingleDefaultInitializerDefinition(llvm::Value* ptr, CompileContext& context)
{
    for (uint64_t index = 0; index < size_; index++)
    {
        llvm::Value* element_ptr = buildGetElementPointer(ptr, index, context);
        element_type_->buildDefaultInitializer(element_ptr, context);
    }
}

void lang::VectorType::buildSingleCopyInitializerDefinition(llvm::Value*    dts_ptr,
                                                            llvm::Value*    src_ptr,
                                                            CompileContext& context)
{
    for (uint64_t index = 0; index < size_; index++)
    {
        llvm::Value* dst_element_ptr = buildGetElementPointer(dts_ptr, index, context);
        llvm::Value* src_element_ptr = buildGetElementPointer(src_ptr, index, context);

        element_type_->buildCopyInitializer(dst_element_ptr, src_element_ptr, context);
    }
}

void lang::VectorType::buildSingleDefaultFinalizerDefinition(llvm::Value* ptr, CompileContext& context)
{
    for (uint64_t index = 0; index < size_; index++)
    {
        llvm::Value* element_ptr = buildGetElementPointer(ptr, index, context);
        element_type_->buildFinalizer(element_ptr, context);
    }
}

std::string lang::VectorType::createMangledName() const
{
    return std::string("(") + element_type_->getMangledName() + ")vx(" + std::to_string(size_) + std::string(")");
}

llvm::DIType* lang::VectorType::createDebugType(CompileContext& context)
{
    const llvm::DataLayout& dl          = context.module()->getDataLayout();
    llvm::Type*             vector_type = getContentType(*context.llvmContext());

    uint64_t      size            = dl.getTypeSizeInBits(vector_type);
    uint32_t      alignment       = dl.getABITypeAlignment(vector_type);
    llvm::DIType* element_di_type = element_type_->getDebugType(context);

    llvm::SmallVector<llvm::Metadata*, 1> subscripts;
    subscripts.push_back(context.di()->getOrCreateSubrange(0, (int64_t) size_));

    return context.di()->createVectorType(size, alignment, element_di_type, context.di()->getOrCreateArray(subscripts));
}

std::vector<lang::TypeDefinition*> lang::VectorType::getDependencies() const
{
    std::vector<lang::TypeDefinition*> dependencies;

    if (element_type_->getDefinition()) dependencies.push_back(element_type_->getDefinition());

    return dependencies;
}

lang::TypeRegistry<uint64_t>& lang::VectorType::getVectorTypes()
{
    static lang::TypeRegistry<uint64_t> vector_types;
    return vector_types;
}

bool lang::VectorType::isTriviallyDefaultConstructible() const
{
    return getElementType()->getDefinition()->isTriviallyDefaultConstructible();
}

bool lang::VectorType::isTriviallyCopyConstructible() const
{
    return getElementType()->getDefinition()->isTriviallyCopyConstructible();
}

bool lang::VectorType::isTriviallyDestructible() const
{
    return getElementType()->getDefinition()->isTriviallyDestructible();
}

lang::TypeDefinitionRegistry* lang::VectorType::getRegistry()
{
    return &getVectorTypes();
}

lang::ResolvingHandle<lang::Type> lang::VectorType::get(lang::ResolvingHandle<lang::Type> element_type, uint64_t size)
{
    element_type = element_type->toSeparateUndefined();

    std::vector<lang::ResolvingHandle<lang::Type>> used_types;
    used_types.push_back(element_type);

    std::optional<lang::ResolvingHandle<lang::Type>> defined_type = getVectorTypes().get(used_types, size);

    if (defined_type.has_value()) { return defined_type.value(); }
    else
    {
        auto*                             vector_type = new lang::VectorType(element_type, size);
        lang::ResolvingHandle<lang::Type> type =
            lang::makeHandled<lang::Type>(std::unique_ptr<lang::VectorType>(vector_type));
        getVectorTypes().add(std::move(used_types), size, type);

        return type;
    }
}

std::shared_ptr<lang::Value> lang::VectorType::createValue(std::vector<std::shared_ptr<lang::Value>> values,
                                                           CompileContext&                           context)
{
    llvm::Value* vector_ptr = context.ir()->CreateAlloca(getContentType(*context.llvmContext()), nullptr, "alloca");

    for (uint64_t index = 0; index < size_; index++)
    {
        values[index]->buildContentValue(context);

        llvm::Value* element_ptr = buildGetElementPointer(vector_ptr, index, context);
        context.ir()->CreateStore(values[index]->getContentValue(), element_ptr);
    }

    return std::make_shared<lang::WrappedNativeValue>(self(), vector_ptr);
}
