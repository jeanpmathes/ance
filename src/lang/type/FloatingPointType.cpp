#include "FloatingPointType.h"

#include "compiler/CompileContext.h"
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

Execution::Type lang::FloatingPointType::createDebugType(CompileContext& context) const
{
    return context.exec().registerFloatingPointType(self());
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

Shared<lang::Value> lang::FloatingPointType::buildImplicitConversion(lang::ResolvingHandle<lang::Type> other,
                                                                     Shared<lang::Value>               value,
                                                                     CompileContext&                   context)
{
    return context.exec().computeConversionOnFP(value, other);
}

bool lang::FloatingPointType::isCastingPossibleTo(lang::Type const& other) const
{
    return other.isFloatingPointType() || other.isFixedWidthIntegerType();
}

bool lang::FloatingPointType::validateCast(lang::Type const&, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::FloatingPointType::buildCast(lang::ResolvingHandle<lang::Type> other,
                                                       Shared<lang::Value>               value,
                                                       CompileContext&                   context)
{
    if (other->isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }))
    {
        return context.exec().computeConversionOnFP(value, other);
    }

    if (other->isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }))
    {
        return context.exec().computeConversionOnFP(value, other);
    }

    throw std::logic_error("Invalid cast");
}

bool lang::FloatingPointType::isOperatorDefined(lang::UnaryOperator op) const
{
    return op == lang::UnaryOperator::NEGATION;
}

lang::ResolvingHandle<lang::Type> lang::FloatingPointType::getOperatorResultType(lang::UnaryOperator)
{
    return self();
}

bool lang::FloatingPointType::validateOperator(lang::UnaryOperator, lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::FloatingPointType::buildOperator(lang::UnaryOperator op,
                                                           Shared<lang::Value> value,
                                                           CompileContext&     context)
{
    return context.exec().performOperator(op, value);
}

bool lang::FloatingPointType::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    if (!op.isArithmetic() && !op.isRelational() && !op.isEquality()) return false;

    lang::Type const& real_other = lang::Type::getReferencedType(other);

    if (real_other.isFloatingPointType()) { return this == real_other.isFloatingPointType(); }

    return false;
}

lang::ResolvingHandle<lang::Type> lang::FloatingPointType::getOperatorResultType(lang::BinaryOperator op,
                                                                                 lang::ResolvingHandle<lang::Type>)
{
    if (op.isArithmetic()) return self()->getActualType();
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

Shared<lang::Value> lang::FloatingPointType::buildOperator(lang::BinaryOperator op,
                                                           Shared<lang::Value>  left,
                                                           Shared<lang::Value>  right,
                                                           CompileContext&      context)
{
    if (left->type()->isReferenceType()) left = context.exec().performDereference(left);

    return context.exec().performOperator(op, left, right);
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
