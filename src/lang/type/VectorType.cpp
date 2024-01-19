#include "VectorType.h"

#include <utility>

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/value/Value.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/SizeType.h"
#include "lang/type/VectorizableType.h"

#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::VectorType::VectorType(lang::ResolvingHandle<lang::Type> element_type, uint64_t size)
    : TypeDefinition(lang::Identifier::like("<" + element_type->name() + "; " + std::to_string(size) + ">"))
    , SequenceType(element_type, size)
{}

lang::VectorType const* lang::VectorType::isVectorType() const
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

lang::ResolvingHandle<lang::Type> lang::VectorType::getActualType()
{
    if (!actual_type_.hasValue())
    {
        lang::ResolvingHandle<lang::Type> actual_element_type = element_type_->getActualType();
        if (actual_element_type == element_type_) { actual_type_ = self(); }
        else { actual_type_ = scope().context().getVectorType(actual_element_type, size_.value()); }
    }

    return actual_type_.value();
}

lang::Type const& lang::VectorType::getActualType() const
{
    const_cast<VectorType*>(this)->getActualType();
    return actual_type_.value();
}

bool lang::VectorType::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    if (size_.value() > MAX_VECTOR_TYPE_SIZE)
    {
        validation_logger.logError("Vector type size cannot be larger than " + std::to_string(MAX_VECTOR_TYPE_SIZE),
                                   location);
        return false;
    }

    if (size_.value() == 0)
    {
        validation_logger.logError("Vector type size cannot be zero", location);
        return false;
    }

    if (lang::Type::isTypeUndefined(element_type_, scope(), element_type_->name().location(), validation_logger))
        return false;

    if (element_type_->isReferenceType())
    {
        validation_logger.logError("Cannot declare vector of reference types", location);
        return false;
    }

    return true;
}

bool lang::VectorType::isImplicitlyConvertibleTo(lang::Type const& other) const
{
    if (auto other_as_vector = other.isVectorType())
    {
        if (other_as_vector->size_.value() != this->size_.value()) return false;

        return element_type_->isImplicitlyConvertibleTo(other.getElementType());
    }

    return false;
}

bool lang::VectorType::validateImplicitConversion(lang::Type const& other,
                                                  lang::Location    location,
                                                  ValidationLogger& validation_logger) const
{
    return element_type_->validateImplicitConversion(other.getElementType(), location, validation_logger);
}

Shared<lang::Value> lang::VectorType::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                              Shared<lang::Value>               value,
                                                              CompileContext&                   context)
{
    if (auto element_vector = element_type_->isVectorizable())
    {
        return element_vector->buildImplicitConversion(other, value, context);
    }
    else
    {
        VectorType* other_as_vector = other->isVectorType();
        assert(other_as_vector != nullptr);

        Shared<lang::Value> result_ptr = context.exec().performStackAllocation(other);

        for (size_t index = 0; index < size_.value(); index++)
        {
            Shared<lang::Constant> index_constant = context.exec().getSizeN(index);

            Shared<lang::Value> current_element_ref = buildSubscriptInBounds(value, index_constant, context);
            Shared<lang::Value> current_element     = context.exec().performDereference(current_element_ref);

            Shared<lang::Value> result_element =
                element_type_->buildImplicitConversion(other->getElementType(), current_element, context);
            Shared<lang::Value> result_dst_ref = buildSubscriptInBounds(result_ptr, index_constant, context);
            Shared<lang::Value> result_dst_ptr = context.exec().computePointerFromReference(result_dst_ref);

            context.exec().performStoreToAddress(result_dst_ptr, result_element);
        }

        Shared<lang::Value> result = context.exec().performLoadFromAddress(result_ptr);

        return result;
    }
}

bool lang::VectorType::isCastingPossibleTo(lang::Type const& other) const
{
    return element_type_->isCastingPossibleTo(other.getElementType());
}

bool lang::VectorType::validateCast(lang::Type const& other,
                                    lang::Location    location,
                                    ValidationLogger& validation_logger) const
{
    return element_type_->validateCast(other.getElementType(), location, validation_logger);
}

Shared<lang::Value> lang::VectorType::buildCast(lang::ResolvingHandle<lang::Type> other,
                                                Shared<lang::Value>               value,
                                                CompileContext&                   context)
{
    if (auto element_vector = element_type_->isVectorizable())
    {
        return element_vector->buildCast(other, value, context);
    }
    else
    {
        VectorType* other_as_vector = other->isVectorType();
        assert(other_as_vector != nullptr);

        Shared<lang::Value> result_ptr = context.exec().performStackAllocation(other);

        for (uint64_t index = 0; index < size_.value(); index++)
        {
            Shared<lang::Constant> index_constant = context.exec().getSizeN(index);

            Shared<lang::Value> current_element_ref = buildSubscriptInBounds(value, index_constant, context);
            Shared<lang::Value> current_element     = context.exec().performDereference(current_element_ref);

            Shared<lang::Value> result_element =
                element_type_->buildCast(other->getElementType(), current_element, context);
            Shared<lang::Value> result_dst_ref = buildSubscriptInBounds(result_ptr, index_constant, context);
            Shared<lang::Value> result_dst_ptr = context.exec().computePointerFromReference(result_dst_ref);

            context.exec().performStoreToAddress(result_dst_ptr, result_element);
        }

        Shared<lang::Value> result = context.exec().performLoadFromAddress(result_ptr);

        return result;
    }
}

bool lang::VectorType::isOperatorDefined(lang::UnaryOperator op) const
{
    return getElementType().isOperatorDefined(op);
}

lang::ResolvingHandle<lang::Type> lang::VectorType::getOperatorResultType(lang::UnaryOperator op)
{
    return scope().context().getVectorType(element_type_->getOperatorResultType(op), size_.value());
}

bool lang::VectorType::validateOperator(lang::UnaryOperator op,
                                        lang::Location      location,
                                        ValidationLogger&   validation_logger) const
{
    return element_type_->validateOperator(op, location, validation_logger);
}

Shared<lang::Value> lang::VectorType::buildOperator(lang::UnaryOperator op,
                                                    Shared<lang::Value> value,
                                                    CompileContext&     context)
{
    if (auto element_vector = element_type_->isVectorizable())
    {
        return element_vector->buildOperator(op, value, context);
    }
    else
    {
        Shared<lang::Value> result_ptr = context.exec().performStackAllocation(getOperatorResultType(op));

        for (uint64_t index = 0; index < size_.value(); index++)
        {
            Shared<lang::Constant> index_constant = context.exec().getSizeN(index);

            Shared<lang::Value> current_element_ref = buildSubscriptInBounds(value, index_constant, context);
            Shared<lang::Value> current_element     = context.exec().performDereference(current_element_ref);

            Shared<lang::Value> result_element = element_type_->buildOperator(op, current_element, context);
            Shared<lang::Value> result_dst_ref = buildSubscriptInBounds(result_ptr, index_constant, context);
            Shared<lang::Value> result_dst_ptr = context.exec().computePointerFromReference(result_dst_ref);

            context.exec().performStoreToAddress(result_dst_ptr, result_element);
        }

        Shared<lang::Value> result = context.exec().performLoadFromAddress(result_ptr);

        return result;
    }
}

bool lang::VectorType::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    if (auto other_as_vector = other.isVectorType())
    {
        if (other_as_vector->size_.value() != this->size_.value()) return false;

        return getElementType().isOperatorDefined(op, other.getElementType());
    }

    return false;
}

lang::ResolvingHandle<lang::Type> lang::VectorType::getOperatorResultType(lang::BinaryOperator              op,
                                                                          lang::ResolvingHandle<lang::Type> other)
{
    return scope().context().getVectorType(element_type_->getOperatorResultType(op, other), size_.value());
}

bool lang::VectorType::validateOperator(lang::BinaryOperator op,
                                        lang::Type const&    other,
                                        lang::Location       left_location,
                                        lang::Location       right_location,
                                        ValidationLogger&    validation_logger) const
{
    return element_type_->validateOperator(op, other, left_location, right_location, validation_logger);
}

Shared<lang::Value> lang::VectorType::buildOperator(lang::BinaryOperator op,
                                                    Shared<lang::Value>  left,
                                                    Shared<lang::Value>  right,
                                                    CompileContext&      context)
{
    if (auto element_vector = element_type_->isVectorizable())
    {
        return element_vector->buildOperator(op, left, right, context);
    }
    else
    {
        VectorType* result_type_as_vector = getOperatorResultType(op, right->type())->isVectorType();
        assert(result_type_as_vector != nullptr);

        Shared<lang::Value> result_ptr =
            context.exec().performStackAllocation(getOperatorResultType(op, right->type()));

        for (uint64_t index = 0; index < size_.value(); index++)
        {
            Shared<lang::Constant> index_constant = context.exec().getSizeN(index);

            Shared<lang::Value> left_element_ref = buildSubscriptInBounds(left, index_constant, context);
            Shared<lang::Value> left_element     = context.exec().performDereference(left_element_ref);

            Shared<lang::Value> right_element_ref = buildSubscriptInBounds(right, index_constant, context);
            Shared<lang::Value> right_element     = context.exec().performDereference(right_element_ref);

            Shared<lang::Value> result_element = element_type_->buildOperator(op, left_element, right_element, context);
            Shared<lang::Value> result_dst_ref = buildSubscriptInBounds(result_ptr, index_constant, context);
            Shared<lang::Value> result_dst_ptr = context.exec().computePointerFromReference(result_dst_ref);

            context.exec().performStoreToAddress(result_dst_ptr, result_element);
        }

        Shared<lang::Value> result = context.exec().performLoadFromAddress(result_ptr);

        return result;
    }
}

bool lang::VectorType::acceptOverloadRequest(std::vector<ResolvingHandle<lang::Type>> parameters)
{
    if (parameters.size() != 1) return false;

    lang::ResolvingHandle<lang::Type> other = parameters.front();

    if (auto other_as_vector = other->isVectorType())
    {
        if (other_as_vector->size_.value() != this->size_.value()) return false;

        std::vector<lang::ResolvingHandle<lang::Type>> element_parameters;
        element_parameters.push_back(other_as_vector->getElementType());

        return element_type_->requestOverload(element_parameters);
    }

    return false;
}

void lang::VectorType::buildRequestedOverload(std::vector<ResolvingHandle<lang::Type>> parameters,
                                              lang::PredefinedFunction&                function,
                                              CompileContext&                          context)
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

        context.exec().enterFunctionBody(function.getFunctionHandle(context));
        {
            Shared<lang::Value> original = function.getArgument(0);

            Shared<lang::Value> result_ptr = context.exec().performStackAllocation(self());

            for (uint64_t index = 0; index < size_.value(); index++)
            {
                Shared<lang::Constant> index_constant = context.exec().getSizeN(index);

                Shared<lang::Value> original_element_ref = buildSubscriptInBounds(original, index_constant, context);
                Shared<lang::Value> original_element     = context.exec().performDereference(original_element_ref);

                std::vector<Shared<lang::Value>> ctor_parameters;
                ctor_parameters.emplace_back(original_element);

                Shared<lang::Value> converted_element = element_ctor->buildCall(ctor_parameters, context);

                Shared<lang::Value> result_element_ref = buildSubscriptInBounds(result_ptr, index_constant, context);
                Shared<lang::Value> result_element_ptr = context.exec().computePointerFromReference(result_element_ref);

                context.exec().performStoreToAddress(result_element_ptr, converted_element);
            }

            Shared<lang::Value> result = context.exec().performLoadFromAddress(result_ptr);
            context.exec().performReturn(result);
        }
    }
}

std::string lang::VectorType::createMangledName() const
{
    return std::string("(") + element_type_->getMangledName() + ")vx(" + std::to_string(size_.value())
         + std::string(")");
}

Execution::Type lang::VectorType::createExecutionType(CompileContext& context) const
{
    return context.exec().registerVectorType(self());
}

Execution::IndexingMode lang::VectorType::getIndexingMode() const
{
    return Execution::IndexingMode::SEQUENCE;
}

lang::ResolvingHandle<lang::Type> lang::VectorType::clone(lang::Context& new_context) const
{
    return new_context.getVectorType(element_type_->getUndefinedTypeClone(new_context), size_.value());
}
