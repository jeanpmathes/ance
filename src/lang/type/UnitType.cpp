#include "UnitType.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/construct/constant/BooleanConstant.h"
#include "lang/type/Type.h"

lang::UnitType::UnitType() : TypeDefinition(lang::Identifier::like("()")) {}

StateCount lang::UnitType::getStateCount() const
{
    return StateCount::unit();
}

std::string lang::UnitType::createMangledName() const
{
    return std::string(name().text());
}

void lang::UnitType::registerExecutionType(Execution& exec) const
{
    return exec.registerUnitType(self());
}

bool lang::UnitType::isUnitType() const
{
    return true;
}

void lang::UnitType::performDefaultInitializer(Shared<lang::Value>, Shared<lang::Value>, Execution&) const
{
    // No runtime initialization required.
}

void lang::UnitType::performCopyInitializer(Shared<lang::Value>, Shared<lang::Value>, Execution&) const
{
    // No runtime copy required.
}

void lang::UnitType::performFinalizer(Shared<lang::Value>, Shared<lang::Value>, Execution&) const
{
    // No runtime finalization required.
}

lang::ResolvingHandle<lang::Type> lang::UnitType::clone(lang::Context& new_context) const
{
    return new_context.getUnitType();
}

bool lang::UnitType::isOperatorDefined(lang::BinaryOperator op, lang::Type const& other) const
{
    return op.isEquality() && other.isUnitType();
}

lang::Type const& lang::UnitType::getOperatorResultType(lang::BinaryOperator, lang::Type const&) const
{
    return scope().context().getBooleanType();
}

bool lang::UnitType::validateOperator(lang::BinaryOperator,
                                      lang::Type const&,
                                      lang::Location,
                                      lang::Location,
                                      ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::UnitType::buildOperator(lang::BinaryOperator op,
                                                  Shared<lang::Value>,
                                                  Shared<lang::Value>,
                                                  Execution& exec) const
{
    if (op == BinaryOperator::EQUAL) return BooleanConstant::createTrue(exec.ctx());

    if (op == BinaryOperator::NOT_EQUAL) return BooleanConstant::createFalse(exec.ctx());

    throw std::logic_error("Unit type does not support operator '" + op.toString() + "'");
}

bool lang::UnitType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::UnitType::isTriviallyCopyConstructible() const
{
    return true;
}

bool lang::UnitType::isTriviallyDestructible() const
{
    return true;
}
