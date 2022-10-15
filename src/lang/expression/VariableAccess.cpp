#include "VariableAccess.h"

#include <utility>

#include "lang/ApplicationVisitor.h"
#include "lang/scope/LocalScope.h"
#include "lang/scope/Scope.h"
#include "validation/ValidationLogger.h"

VariableAccess::VariableAccess(lang::ResolvingHandle<lang::Variable> variable, lang::Location location)
    : Expression(location)
    , variable_(std::move(variable))
{}

lang::ResolvingHandle<lang::Variable> VariableAccess::variable() const
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

std::optional<lang::ResolvingHandle<lang::Type>> VariableAccess::tryGetType() const
{
    if (variable_->isDefined() && variable_->type()->isDefined()) return variable_->type();
    else return std::nullopt;
}

bool VariableAccess::isNamed()
{
    return true;
}

bool VariableAccess::validate(ValidationLogger& validation_logger) const
{
    if (isVariableDropped(validation_logger)) return false;
    return variable_->validateGetValue(validation_logger, location());
}

bool VariableAccess::validateAssignment(const std::shared_ptr<lang::Value>& value,
                                        lang::Location                      value_location,
                                        ValidationLogger&                   validation_logger)
{
    if (isVariableDropped(validation_logger)) return false;

    return variable_->validateSetValue(value, validation_logger, location(), value_location);
}

bool VariableAccess::isVariableDropped(ValidationLogger& validation_logger) const
{
    if (!variable_->isDefined() && scope()->asLocalScope()->wasVariableDropped(variable_))
    {
        validation_logger.logError("Variable with name '" + variable_->name() + "' was dropped", location());
        return true;
    }

    return false;
}

Expression::Expansion VariableAccess::expandWith(Expressions) const
{
    return {Statements(), std::make_unique<VariableAccess>(variable_->toUndefined(), location()), Statements()};
}

void VariableAccess::doBuild(CompileContext& context)
{
    std::shared_ptr<lang::Value> value = variable_->getValue(context);
    setValue(value);
}

void VariableAccess::doAssign(std::shared_ptr<lang::Value> value, CompileContext& context)
{
    variable_->setValue(value, context);
}

VariableAccess::~VariableAccess() = default;
