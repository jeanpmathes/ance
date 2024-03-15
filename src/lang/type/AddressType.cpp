#include "AddressType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/Value.h"
#include "lang/type/SizeType.h"
#include "lang/type/Type.h"

lang::AddressType const* lang::AddressType::isAddressType() const
{
    return this;
}

StateCount lang::AddressType::getStateCount() const
{
    return SpecialCount::ABSTRACT;
}

bool lang::AddressType::isCastingPossibleTo(lang::Type const& other) const
{
    if (getStateCount().isUnit()) return false;

    auto* other_address = other.isAddressType();

    bool const cast_to_other_address = other.isAddressType()
                                    && (this->getPointeeType() == nullptr || other_address->getPointeeType() == nullptr
                                        || lang::Type::areSame(*getPointeeType(), *other_address->getPointeeType()));

    return cast_to_other_address || other.isUnsignedIntegerPointerType();
}

bool lang::AddressType::validateCast(lang::Type const&, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::AddressType::buildCast(lang::Type const& other,
                                                 Shared<lang::Value>               value,
                                                 CompileContext&                   context) const
{
    if (other.isAddressType())
    { return context.exec().computeCastedAddress(value, other); }

    if (other.isUnsignedIntegerPointerType())
    { return context.exec().computePointerToInteger(value); }

    throw std::logic_error("Invalid cast");
}

bool lang::AddressType::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    lang::Type const& real_other = lang::Type::getReferencedType(other);

    if (op.isEquality() || (op == lang::BinaryOperator::SUBTRACTION && getPointeeType() != nullptr))
    {
        return lang::Type::areSame(real_other, self());
    }

    if (op == lang::BinaryOperator::ADDITION && getPointeeType() != nullptr)
    {
        // The type 'size' is allowed here only because implicit conversion for operators does not work yet.
        return real_other.isSizeType() || real_other.isDiffType();
    }

    return false;
}

lang::Type const& lang::AddressType::getOperatorResultType(lang::BinaryOperator op,
                                                           lang::Type const&) const
{
    if (op.isEquality()) return scope().context().getBooleanType();

    if (op == lang::BinaryOperator::ADDITION) return self();

    if (op == lang::BinaryOperator::SUBTRACTION) return scope().context().getDiffType();

    return lang::Type::getUndefined();
}

bool lang::AddressType::validateOperator(lang::BinaryOperator,
                                         lang::Type const&,
                                         lang::Location,
                                         lang::Location,
                                         ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::AddressType::buildOperator(lang::BinaryOperator op,
                                                     Shared<lang::Value>  left,
                                                     Shared<lang::Value>  right,
                                                     CompileContext&      context) const
{
    if (right->type().isReferenceType()) right = context.exec().performDereference(right);

    if (op.isEquality())
    {
        Shared<lang::Value> left_as_integer  = context.exec().computePointerToInteger(left);
        Shared<lang::Value> right_as_integer = context.exec().computePointerToInteger(right);

        return context.exec().performOperator(op, left_as_integer, right_as_integer);
    }

    if (op == lang::BinaryOperator::ADDITION)
    {
        if (getPointeeType()->getStateCount().isUnit())
            return context.exec().getDefault(getOperatorResultType(op, right->type()));
        else
        {
            if (right->type().isSizeType())
                right = right->type().buildImplicitConversion(context.ctx().getDiffType(), right, context);
            Shared<lang::Value> pointer =
                context.exec().computeElementPointer(left, right, Execution::IndexingMode::POINTER, std::nullopt);
            return context.exec().computeCastedAddress(pointer, self());
        }
    }

    if (op == lang::BinaryOperator::SUBTRACTION) { return context.exec().computeAddressDiff(left, right); }

    throw std::logic_error("Invalid operator for address type");
}
