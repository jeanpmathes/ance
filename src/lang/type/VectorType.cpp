#include "VectorType.h"

#include <utility>

#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/Value.h"
#include "lang/type/ReferenceType.h"
#include "lang/type/SizeType.h"
#include "lang/type/VectorizableType.h"
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

Shared<lang::Value> lang::VectorType::execImplicitConversion(lang::Type const&   other,
                                                             Shared<lang::Value> value,
                                                              Execution&          exec) const
{
    if (auto element_vector = element_type_->isVectorizable())
    {
        return element_vector->execImplicitConversion(other, value, exec);
    }
    else
    {
        VectorType const* other_as_vector = other.isVectorType();
        assert(other_as_vector != nullptr);

        Shared<lang::Value> result_ptr = exec.performStackAllocation(other);

        for (size_t index = 0; index < size_.value(); index++)
        {
            Shared<lang::Constant> index_constant = exec.getSizeN(index);

            Shared<lang::Value> current_element_ref = execSubscriptInBounds(value, index_constant, exec);
            Shared<lang::Value> current_element     = exec.performDereference(current_element_ref);

            Shared<lang::Value> result_element =
                element_type_->execImplicitConversion(other.getElementType(), current_element, exec);
            Shared<lang::Value> result_dst_ref = execSubscriptInBounds(result_ptr, index_constant, exec);
            Shared<lang::Value> result_dst_ptr = exec.computePointerFromReference(result_dst_ref);

            exec.performStoreToAddress(result_dst_ptr, result_element);
        }

        Shared<lang::Value> result = exec.performLoadFromAddress(result_ptr);

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

Shared<lang::Value> lang::VectorType::execCast(lang::Type const&   other,
                                               Shared<lang::Value> value,
                                                Execution&          exec) const
{
    if (auto element_vector = element_type_->isVectorizable()) { return element_vector->execCast(other, value, exec); }
    else
    {
        VectorType const* other_as_vector = other.isVectorType();
        assert(other_as_vector != nullptr);

        Shared<lang::Value> result_ptr = exec.performStackAllocation(other);

        for (uint64_t index = 0; index < size_.value(); index++)
        {
            Shared<lang::Constant> index_constant = exec.getSizeN(index);

            Shared<lang::Value> current_element_ref = execSubscriptInBounds(value, index_constant, exec);
            Shared<lang::Value> current_element     = exec.performDereference(current_element_ref);

            Shared<lang::Value> result_element = element_type_->execCast(other.getElementType(), current_element, exec);
            Shared<lang::Value> result_dst_ref = execSubscriptInBounds(result_ptr, index_constant, exec);
            Shared<lang::Value> result_dst_ptr = exec.computePointerFromReference(result_dst_ref);

            exec.performStoreToAddress(result_dst_ptr, result_element);
        }

        Shared<lang::Value> result = exec.performLoadFromAddress(result_ptr);

        return result;
    }
}

bool lang::VectorType::isOperatorDefined(lang::UnaryOperator op) const
{
    return getElementType().isOperatorDefined(op);
}

lang::Type const& lang::VectorType::getOperatorResultType(lang::UnaryOperator op) const
{
    return scope().context().getVectorType(element_type_->getOperatorResultType(op), size_.value());
}

bool lang::VectorType::validateOperator(lang::UnaryOperator op,
                                        lang::Location      location,
                                        ValidationLogger&   validation_logger) const
{
    return element_type_->validateOperator(op, location, validation_logger);
}

Shared<lang::Value> lang::VectorType::execOperator(lang::UnaryOperator op,
                                                   Shared<lang::Value> value,
                                                    Execution&          exec) const
{
    if (auto element_vector = element_type_->isVectorizable())
    { return element_vector->execOperator(op, value, exec); }
    else
    {
        Shared<lang::Value> result_ptr = exec.performStackAllocation(getOperatorResultType(op));

        for (uint64_t index = 0; index < size_.value(); index++)
        {
            Shared<lang::Constant> index_constant = exec.getSizeN(index);

            Shared<lang::Value> current_element_ref = execSubscriptInBounds(value, index_constant, exec);
            Shared<lang::Value> current_element     = exec.performDereference(current_element_ref);

            Shared<lang::Value> result_element = element_type_->execOperator(op, current_element, exec);
            Shared<lang::Value> result_dst_ref = execSubscriptInBounds(result_ptr, index_constant, exec);
            Shared<lang::Value> result_dst_ptr = exec.computePointerFromReference(result_dst_ref);

            exec.performStoreToAddress(result_dst_ptr, result_element);
        }

        Shared<lang::Value> result = exec.performLoadFromAddress(result_ptr);

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

lang::Type const& lang::VectorType::getOperatorResultType(lang::BinaryOperator op, lang::Type const& other) const
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

Shared<lang::Value> lang::VectorType::execOperator(lang::BinaryOperator op,
                                                   Shared<lang::Value>  left,
                                                    Shared<lang::Value>  right,
                                                    Execution&           exec) const
{
    if (auto element_vector = element_type_->isVectorizable())
    {
        return element_vector->execOperator(op, left, right, exec);
    }
    else
    {
        VectorType const* result_type_as_vector = getOperatorResultType(op, right->type()).isVectorType();
        assert(result_type_as_vector != nullptr);

        Shared<lang::Value> result_ptr = exec.performStackAllocation(getOperatorResultType(op, right->type()));

        for (uint64_t index = 0; index < size_.value(); index++)
        {
            Shared<lang::Constant> index_constant = exec.getSizeN(index);

            Shared<lang::Value> left_element_ref = execSubscriptInBounds(left, index_constant, exec);
            Shared<lang::Value> left_element     = exec.performDereference(left_element_ref);

            Shared<lang::Value> right_element_ref = execSubscriptInBounds(right, index_constant, exec);
            Shared<lang::Value> right_element     = exec.performDereference(right_element_ref);

            Shared<lang::Value> result_element = element_type_->execOperator(op, left_element, right_element, exec);
            Shared<lang::Value> result_dst_ref = execSubscriptInBounds(result_ptr, index_constant, exec);
            Shared<lang::Value> result_dst_ptr = exec.computePointerFromReference(result_dst_ref);

            exec.performStoreToAddress(result_dst_ptr, result_element);
        }

        Shared<lang::Value> result = exec.performLoadFromAddress(result_ptr);

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

void lang::VectorType::execRequestedOverload(std::vector<std::reference_wrapper<lang::Type const>> parameters,
                                             lang::PredefinedFunction&                             function,
                                              Execution&                                            exec) const
{
    lang::Type const& other_type         = parameters.front();
    lang::Type const& other_element_type = other_type.getElementType();

    if (auto element_vector = element_type_->isVectorizable())
    {
        element_vector->execRequestedOverload(other_element_type, self(), function, exec);
    }
    else
    {
        std::vector<std::reference_wrapper<lang::Function const>> overloads =
            element_type_->resolveOverload({other_element_type});

        assert(overloads.size() == 1);

        lang::Function const* element_ctor = &overloads.front().get();

        exec.defineFunctionBody(function.function(), [this, element_ctor](Execution::FnCtx& ctx) {
            Shared<lang::Value> original = ctx.getParameterValue(0);

            Shared<lang::Value> result_ptr = ctx.exec().performStackAllocation(self());

            for (uint64_t index = 0; index < size_.value(); index++)
            {
                Shared<lang::Constant> index_constant = ctx.exec().getSizeN(index);

                Shared<lang::Value> original_element_ref = execSubscriptInBounds(original, index_constant, ctx.exec());
                Shared<lang::Value> original_element     = ctx.exec().performDereference(original_element_ref);

                std::vector<Shared<lang::Value>> ctor_parameters;
                ctor_parameters.emplace_back(original_element);

                Shared<lang::Value> converted_element = element_ctor->execCall(ctor_parameters, ctx.exec());

                Shared<lang::Value> result_element_ref = execSubscriptInBounds(result_ptr, index_constant, ctx.exec());
                Shared<lang::Value> result_element_ptr = ctx.exec().computePointerFromReference(result_element_ref);

                ctx.exec().performStoreToAddress(result_element_ptr, converted_element);
            }

            Shared<lang::Value> result = ctx.exec().performLoadFromAddress(result_ptr);
            ctx.exec().performReturn(result);
        });
    }
}

std::string lang::VectorType::createMangledName() const
{
    return std::string("(") + element_type_->getMangledName() + ")vx(" + std::to_string(size_.value())
         + std::string(")");
}

void lang::VectorType::registerExecutionType(Execution& exec) const
{
    return exec.registerVectorType(self());
}

Execution::IndexingMode lang::VectorType::getIndexingMode() const
{
    return Execution::IndexingMode::SEQUENCE;
}

lang::ResolvingHandle<lang::Type> lang::VectorType::clone(lang::Context& new_context) const
{
    return new_context.getVectorType(element_type_->getUndefinedTypeClone(new_context), size_.value());
}
