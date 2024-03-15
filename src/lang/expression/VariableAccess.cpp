#include "VariableAccess.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

VariableAccess::VariableAccess(lang::ResolvingHandle<lang::Variable> variable, bool is_defined, lang::Location location)
    : Expression(location)
    , variable_(std::move(variable))
    , is_defined_(is_defined)
{}

lang::Entity const& VariableAccess::variable() const
{
    return *variable_;
}

void VariableAccess::walkDefinitions()
{
    scope().registerUsage(variable_, !is_defined_);
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
    if (lang::Type::checkMismatch<lang::Variable>(variable_, "value", location(), validation_logger)) return false;

    if (isVariableErased(validation_logger)) return false;

    if (!is_defined_)
    {
        validation_logger.logError("No read from uninitialized '" + variable_->name() + "' allowed", location());
        return false;
    }

    return variable_.as<lang::Variable>()->validateGetValue(validation_logger, location());
}

bool VariableAccess::validateAssignment(lang::Type const& value_type,
                                        lang::Location     value_location,
                                        ValidationLogger&  validation_logger) const
{
    if (lang::Type::checkMismatch<lang::Variable>(variable_, "value", location(), validation_logger)) return false;

    if (isVariableErased(validation_logger)) return false;

    return variable_.as<lang::Variable>()->validateSetValue(value_type, validation_logger, location(), value_location);
}

bool VariableAccess::isVariableErased(ValidationLogger& validation_logger) const
{
    if (!variable_->isDefined() && scope().asOrderedScope()->wasEntityErased(variable_))
    {
        validation_logger.logError("Variable with name '" + variable_->name() + "' was erased", location());
        return true;
    }

    return false;
}

Expression::Expansion VariableAccess::expandWith(Expressions, lang::Context& new_context) const
{
    return {
        Statements(),
        makeOwned<VariableAccess>(variable_->getUndefinedClone<lang::Variable>(new_context), is_defined_, location()),
        Statements()};
}

VariableAccess::~VariableAccess() = default;
