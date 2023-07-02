#include "VariableAccess.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/LocalScope.h"
#include "lang/scope/Scope.h"
#include "validation/ValidationLogger.h"

VariableAccess::VariableAccess(lang::ResolvingHandle<lang::Variable> variable, lang::Location location)
    : Expression(location)
    , variable_(std::move(variable))
{}

lang::Variable const& VariableAccess::variable() const
{
    return variable_;
}

void VariableAccess::walkDefinitions()
{
    scope()->registerUsage(variable_);
}

void VariableAccess::postResolve()
{
    Expression::postResolve();

    if (variable_->isDefined()) { scope()->addDependency(variable_); }
}

void VariableAccess::defineType(lang::ResolvingHandle<lang::Type> type)
{
    type.reroute(variable_->type());
}

bool VariableAccess::isNamed() const
{
    return true;
}

bool VariableAccess::validate(ValidationLogger& validation_logger) const
{
    if (isVariableDropped(validation_logger)) return false;
    return variable_->validateGetValue(validation_logger, location());
}

bool VariableAccess::validateAssignment(lang::Value const& value,
                                        lang::Location     value_location,
                                        ValidationLogger&  validation_logger) const
{
    if (isVariableDropped(validation_logger)) return false;
    return variable_->validateSetValue(value, validation_logger, location(), value_location);
}

bool VariableAccess::isVariableDropped(ValidationLogger& validation_logger) const
{
    if (!variable_->isDefined() && scope()->asOrderedScope()->wasVariableDropped(variable_))
    {
        validation_logger.logError("Variable with name '" + variable_->name() + "' was dropped", location());
        return true;
    }

    return false;
}

Expression::Expansion VariableAccess::expandWith(Expressions, lang::Context&) const
{
    return {Statements(), makeOwned<VariableAccess>(variable_->toUndefined(), location()), Statements()};
}

void VariableAccess::doBuild(CompileContext& context)
{
    Shared<lang::Value> value = type()->getStateCount().isUnit()
                                  ? lang::WrappedNativeValue::makeDefault(type(), context)
                                  : variable_->getValue(context);

    setValue(value);
}

void VariableAccess::doAssign(Shared<lang::Value> value, CompileContext& context)
{
    variable_->setValue(value, context);
}

VariableAccess::~VariableAccess() = default;
