#include "VectorType.h"

#include <utility>

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/value/Value.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/SizeType.h"
#include "lang/type/VectorizableType.h"
#include "lang/utility/Values.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::VectorType::VectorType(lang::ResolvingHandle<lang::Type> element_type, uint64_t size)
    : TypeDefinition(lang::Identifier::from("<" + element_type->name() + "; " + std::to_string(size) + ">"))
    , SequenceType(element_type, size)
{}

const lang::VectorType* lang::VectorType::isVectorType() const
{
    return this;
}

lang::VectorType* lang::VectorType::isVectorType()
{
    return this;
}

bool lang::VectorType::isSigned() const
{
    return element_type_->isSigned();
}

lang::ResolvingHandle<lang::Type> lang::VectorType::getActualType() const
{
    lang::ResolvingHandle<lang::Type> actual_element_type = element_type_->getActualType();
    if (actual_element_type == element_type_) { return self(); }
    else { return lang::VectorType::get(actual_element_type, size_.value()); }
}

llvm::Constant* lang::VectorType::getDefaultContent(llvm::Module& m)
{
    std::vector<llvm::Constant*> content(size_.value(), element_type_->getDefaultContent(m));
    return llvm::ConstantVector::get(content);
}

llvm::Type* lang::VectorType::getContentType(llvm::LLVMContext& c) const
{
    llvm::Type* content_type;

    if (element_type_->isVectorizable())
    {
        content_type =
            llvm::FixedVectorType::get(element_type_->getContentType(c), static_cast<unsigned>(size_.value()));
    }
    else { content_type = llvm::ArrayType::get(element_type_->getContentType(c), size_.value()); }

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

    if (lang::validation::isTypeUndefined(element_type_, element_type_->name().location(), validation_logger))
        return false;

    if (element_type_->isReferenceType())
    {
        validation_logger.logError("Cannot declare vector of reference types", location);
        return false;
    }

    return true;
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
        return element_vector->buildImplicitConversion(other, value, context);
    }
    else
    {
        llvm::Value* result_ptr =
            context.ir()->CreateAlloca(other->getContentType(*context.llvmContext()), nullptr, "alloca");

        VectorType* other_as_vector = other->isVectorType();

        value->buildNativeValue(context);

        for (uint64_t index = 0; index < size_; index++)
        {
            llvm::Constant* index_content =
                llvm::ConstantInt::get(lang::SizeType::getSize()->getContentType(*context.llvmContext()), index);

            auto index_value = [&]() {
                llvm::Value* index_native =
                    lang::Values::contentToNative(lang::SizeType::getSize(), index_content, context);
                return std::make_shared<lang::WrappedNativeValue>(lang::SizeType::getSize(), index_native);
            };

            auto current_element = lang::Type::getValueOrReferencedValue(
                buildSubscript(lang::Values::clone(value), index_value(), context),
                context);

            auto result_element =
                element_type_->buildImplicitConversion(other->getElementType(), current_element, context);
            result_element->buildContentValue(context);

            llvm::Value* result_dst_ptr = other_as_vector->buildGetElementPointer(result_ptr, index, context);
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
    return get(element_type_->getOperatorResultType(op, other), size_.value());
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

        VectorType* result_type_as_vector = getOperatorResultType(op, right->type())->isVectorType();

        left->buildNativeValue(context);
        right->buildNativeValue(context);

        for (uint64_t index = 0; index < size_; index++)
        {
            llvm::Constant* index_content =
                llvm::ConstantInt::get(lang::SizeType::getSize()->getContentType(*context.llvmContext()), index);

            auto index_value = [&]() {
                llvm::Value* index_native =
                    lang::Values::contentToNative(lang::SizeType::getSize(), index_content, context);
                return std::make_shared<lang::WrappedNativeValue>(lang::SizeType::getSize(), index_native);
            };

            auto left_element = lang::Type::getValueOrReferencedValue(
                left->type()->buildSubscript(lang::Values::clone(left), index_value(), context),
                context);
            auto right_element = lang::Type::getValueOrReferencedValue(
                right->type()->buildSubscript(lang::Values::clone(right), index_value(), context),
                context);

            auto result_element = element_type_->buildOperator(op, left_element, right_element, context);
            result_element->buildContentValue(context);

            llvm::Value* result_dst_ptr = result_type_as_vector->buildGetElementPointer(result_ptr, index, context);
            context.ir()->CreateStore(result_element->getContentValue(), result_dst_ptr);
        }

        return std::make_shared<lang::WrappedNativeValue>(getOperatorResultType(op, right->type()), result_ptr);
    }
}

bool lang::VectorType::acceptOverloadRequest(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters)
{
    if (parameters.size() != 1) return false;

    lang::ResolvingHandle<lang::Type> other = parameters.front();

    if (auto other_as_vector = other->isVectorType())
    {
        if (other_as_vector->size_ != this->size_) return false;

        return element_type_->requestOverload({other->getElementType()});
    }

    return false;
}

void lang::VectorType::buildRequestedOverload(const std::vector<lang::ResolvingHandle<lang::Type>>& parameters,
                                              lang::PredefinedFunction&                             function,
                                              CompileContext&                                       context)
{
    lang::ResolvingHandle<lang::Type> other_type         = parameters.front();
    lang::ResolvingHandle<lang::Type> other_element_type = other_type->getElementType();

    if (auto element_vector = element_type_->isVectorizable())
    {
        element_vector->buildRequestedOverload(other_element_type, self(), function, context);
    }
    else
    {
        std::vector<lang::ResolvingHandle<Function>> overloads = element_type_->resolveOverload({other_element_type});

        assert(overloads.size() == 1);
        lang::ResolvingHandle<Function> element_ctor = overloads.front();

        llvm::Function* native_function;
        std::tie(std::ignore, native_function) = function.getNativeRepresentation();

        llvm::BasicBlock* block = llvm::BasicBlock::Create(*context.llvmContext(), "block", native_function);
        context.ir()->SetInsertPoint(block);
        {
            llvm::Value* original_content = native_function->getArg(0);
            llvm::Value* original_native  = lang::Values::contentToNative(other_type, original_content, context);

            std::shared_ptr<lang::Value> original_value =
                std::make_shared<lang::WrappedNativeValue>(other_type, original_native);

            llvm::Value* result_ptr =
                context.ir()->CreateAlloca(getContentType(*context.llvmContext()), nullptr, "alloca");

            for (uint64_t index = 0; index < size_; index++)
            {
                llvm::Constant* index_content =
                    llvm::ConstantInt::get(lang::SizeType::getSize()->getContentType(*context.llvmContext()), index);

                auto index_value = [&]() {
                    llvm::Value* index_native =
                        lang::Values::contentToNative(lang::SizeType::getSize(), index_content, context);
                    return std::make_shared<lang::WrappedNativeValue>(lang::SizeType::getSize(), index_native);
                };

                auto element_ref       = other_type->buildSubscript(original_value, index_value(), context);
                auto original_element  = lang::Type::getValueOrReferencedValue(element_ref, context);
                auto converted_element = element_ctor->buildCall({original_element}, context);

                converted_element->buildContentValue(context);

                llvm::Value* result_dst_ptr = buildGetElementPointer(result_ptr, index, context);
                context.ir()->CreateStore(converted_element->getContentValue(), result_dst_ptr);
            }

            llvm::Value* converted = lang::Values::nativeToContent(self(), result_ptr, context);

            context.ir()->CreateRet(converted);
        }
    }
}

std::string lang::VectorType::createMangledName() const
{
    return std::string("(") + element_type_->getMangledName() + ")vx(" + std::to_string(size_.value())
         + std::string(")");
}

llvm::DIType* lang::VectorType::createDebugType(CompileContext& context)
{
    const llvm::DataLayout& dl          = context.module()->getDataLayout();
    llvm::Type*             vector_type = getContentType(*context.llvmContext());

    uint64_t      size            = dl.getTypeSizeInBits(vector_type);
    auto          alignment       = static_cast<uint32_t>(dl.getABITypeAlignment(vector_type));
    llvm::DIType* element_di_type = element_type_->getDebugType(context);

    llvm::SmallVector<llvm::Metadata*, 1> subscripts;
    subscripts.push_back(context.di()->getOrCreateSubrange(0, static_cast<int64_t>(size_.value())));

    return context.di()->createVectorType(size, alignment, element_di_type, context.di()->getOrCreateArray(subscripts));
}

lang::TypeRegistry<uint64_t>& lang::VectorType::getVectorTypes()
{
    static lang::TypeRegistry<uint64_t> vector_types;
    return vector_types;
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
    return SequenceType::createValue(std::move(values), context);
}
