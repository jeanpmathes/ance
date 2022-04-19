#include "Drop.h"

#include <utility>

#include "lang/scope/LocalScope.h"
#include "lang/scope/Scope.h"

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
    scope()->asLocalScope()->drop(variable_);
}

void Drop::validate(ValidationLogger&)
{
    // todo
}

void Drop::doBuild(CompileContext*)
{
    // No code to build yet.
}
