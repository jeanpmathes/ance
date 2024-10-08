#include "FloatingPointType.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/Type.h"

StateCount lang::FloatingPointType::getStateCount() const
{
    return SpecialCount::UNCOUNTABLE;
}

std::string lang::FloatingPointType::createMangledName() const
{
    return std::string(name().text());
}

void lang::FloatingPointType::registerExecutionType(Execution& exec) const
{
    return exec.registerFloatingPointType(self());
}

lang::FloatingPointType const* lang::FloatingPointType::isFloatingPointType() const
{
    return this;
}

bool lang::FloatingPointType::isFloatingPointType(size_t precision) const
{
    return precision == getPrecision();
}

bool lang::FloatingPointType::isImplicitlyConvertibleTo(lang::Type const& other) const
{
    if (auto other_float = other.isFloatingPointType()) { return getPrecision() < other_float->getPrecision(); }

    return false;
}

bool lang::FloatingPointType::validateImplicitConversion(lang::Type const&, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::FloatingPointType::execImplicitConversion(lang::Type const&   other,
                                                                    Shared<lang::Value> value,
                                                                     Execution&          exec) const
{
    return exec.computeConversionOnFP(value, other);
}

bool lang::FloatingPointType::isCastingPossibleTo(lang::Type const& other) const
{
    return other.isFloatingPointType() || other.isFixedWidthIntegerType();
}

bool lang::FloatingPointType::validateCast(lang::Type const&, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::FloatingPointType::execCast(lang::Type const&   other,
                                                      Shared<lang::Value> value,
                                                       Execution&          exec) const
{
    if (other.isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }))
    {
        return exec.computeConversionOnFP(value, other);
    }

    if (other.isXOrVectorOfX([](auto& t) { return t.isFixedWidthIntegerType(); }))
    {
        return exec.computeConversionFP2I(value, other);
    }

    throw std::logic_error("Invalid cast");
}

bool lang::FloatingPointType::isOperatorDefined(lang::UnaryOperator op) const
{
    return op == lang::UnaryOperator::NEGATION;
}

lang::Type const& lang::FloatingPointType::getOperatorResultType(lang::UnaryOperator) const
{
    return self();
}

bool lang::FloatingPointType::validateOperator(lang::UnaryOperator, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::FloatingPointType::execOperator(lang::UnaryOperator op,
                                                          Shared<lang::Value> value,
                                                           Execution&          exec) const
{
    return exec.performOperator(op, value);
}

bool lang::FloatingPointType::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    if (!op.isArithmetic() && !op.isRelational() && !op.isEquality()) return false;

    lang::Type const& real_other = lang::Type::getReferencedType(other);

    if (real_other.isFloatingPointType()) { return this == real_other.isFloatingPointType(); }

    return false;
}

lang::Type const& lang::FloatingPointType::getOperatorResultType(lang::BinaryOperator op, lang::Type const&) const
{
    if (op.isArithmetic()) return self().getActualType();
    if (op.isRelational() || op.isEquality()) return scope().context().getBooleanType();

    return lang::Type::getUndefined();
}

bool lang::FloatingPointType::validateOperator(lang::BinaryOperator,
                                               lang::Type const&,
                                               lang::Location,
                                               lang::Location,
                                               ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::FloatingPointType::execOperator(lang::BinaryOperator op,
                                                          Shared<lang::Value>  left,
                                                           Shared<lang::Value>  right,
                                                           Execution&           exec) const
{
    if (left->type().isReferenceType()) left = exec.performDereference(left);

    return exec.performOperator(op, left, right);
}

bool lang::FloatingPointType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::FloatingPointType::isTriviallyCopyConstructible() const
{
    return true;
}

bool lang::FloatingPointType::isTriviallyDestructible() const
{
    return true;
}
