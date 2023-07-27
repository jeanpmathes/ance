#include "VariableAccess.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/Scope.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

VariableAccess::VariableAccess(lang::ResolvingHandle<lang::Variable> variable, lang::Location location)
    : Expression(location)
    , variable_(std::move(variable))
{}

lang::Variable const& VariableAccess::variable() const
{
    return *variable_.as<lang::Variable>();
}

void VariableAccess::walkDefinitions()
{
    scope()->registerUsage(variable_);
}

void VariableAccess::defineType(lang::ResolvingHandle<lang::Type> type)
{
    Optional<lang::ResolvingHandle<lang::Variable>> variable = variable_.as<lang::Variable>();

    if (!variable.hasValue()) return;

    type.reroute(variable.value()->type());
}

bool VariableAccess::isNamed() const
{
    return true;
}

bool VariableAccess::validate(ValidationLogger& validation_logger) const
{
    if (lang::validation::isUndefined(variable_, scope(), location(), validation_logger)) return false;
    if (lang::Type::checkMismatch<lang::Variable>(variable_, "value", location(), validation_logger)) return false;

    if (isVariableDropped(validation_logger)) return false;

    return variable_.as<lang::Variable>()->validateGetValue(validation_logger, location());
}

bool VariableAccess::validateAssignment(lang::Value const& value,
                                        lang::Location     value_location,
                                        ValidationLogger&  validation_logger) const
{
    if (lang::validation::isUndefined(variable_, scope(), location(), validation_logger)) return false;
    if (lang::Type::checkMismatch<lang::Variable>(variable_, "value", location(), validation_logger)) return false;

    if (isVariableDropped(validation_logger)) return false;

    return variable_.as<lang::Variable>()->validateSetValue(value, validation_logger, location(), value_location);
}

bool VariableAccess::isVariableDropped(ValidationLogger& validation_logger) const
{
    if (!variable_->isDefined() && scope()->asOrderedScope()->wasEntityDropped(variable_))
    {
        validation_logger.logError("Variable with name '" + variable_->name() + "' was dropped", location());
        return true;
    }

    return false;
}

Expression::Expansion VariableAccess::expandWith(Expressions, lang::Context& new_context) const
{
    return {Statements(),
            makeOwned<VariableAccess>(variable_->getUndefinedClone<lang::Variable>(new_context), location()),
            Statements()};
}

void VariableAccess::doBuild(CompileContext& context)
{
    auto variable = lang::Type::makeMatching<lang::Variable>(variable_);

    Shared<lang::Value> value = type()->getStateCount().isUnit()
                                  ? lang::WrappedNativeValue::makeDefault(type(), context)
                                  : variable->getValue(context);

    setValue(value);
}

void VariableAccess::doAssign(Shared<lang::Value> value, CompileContext& context)
{
    auto variable = lang::Type::makeMatching<lang::Variable>(variable_);

    variable->setValue(value, context);
}

VariableAccess::~VariableAccess() = default;
