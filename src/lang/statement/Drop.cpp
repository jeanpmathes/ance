#include "Drop.h"

#include <utility>

#include "lang/ApplicationVisitor.h"
#include "lang/scope/LocalScope.h"
#include "lang/scope/Scope.h"
#include "validation/ValidationLogger.h"

Drop::Drop(lang::ResolvingHandle<lang::Variable> variable, lang::Location location)
    : Statement(location)
    , variable_(std::move(variable))
{}

lang::ResolvingHandle<lang::Variable> Drop::variable() const
{
    return variable_;
}

void Drop::walkDefinitions()
{
    scope()->registerUsage(variable_);
    dropped_ = scope()->asLocalScope()->drop(variable_);
}

void Drop::validate(ValidationLogger& validation_logger) const
{
    if (!variable_->isDefined())
    {
        validation_logger.logError("Name '" + variable_->name() + "' not defined in the current context",
                                   variable_->name().location());
        return;
    }

    if (!dropped_)
    {
        validation_logger.logError("Cannot drop variable '" + variable_->name() + "' which is declared in outer scope",
                                   location());
        return;
    }
}

Statements Drop::expandWith(Expressions, Statements) const
{
    Statements statements;

    statements.push_back(std::make_unique<Drop>(variable_->toUndefined(), location()));

    return statements;
}

void Drop::doBuild(CompileContext& context)
{
    variable_->buildFinalization(context);
}
