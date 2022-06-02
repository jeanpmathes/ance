#include "Drop.h"

#include <utility>

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

void Drop::validate(ValidationLogger& validation_logger)
{
    if (!variable_->isDefined())
    {
        validation_logger.logError("Name '" + variable_->identifier() + "' not defined in the current context",
                                   location());
        return;
    }

    if (!dropped_)
    {
        validation_logger.logError("Cannot drop variable '" + variable_->identifier()
                                       + "' which is declared in outer scope",
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

void Drop::doBuild(CompileContext*)
{
    // No code to build yet.
}