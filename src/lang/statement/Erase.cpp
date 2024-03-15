#include "Erase.h"

#include <utility>

#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

Erase::Erase(lang::ResolvingHandle<lang::Variable> variable, lang::Location location)
    : Statement(location)
    , variable_(std::move(variable))
{}

lang::ResolvingHandle<lang::Entity> Erase::variable()
{
    return variable_;
}

lang::Entity const& Erase::variable() const
{
    return *variable_;
}

void Erase::walkDefinitions()
{
    scope().registerUsage(variable_);
    erased_ = scope().asOrderedScope()->erase(variable_);
}

void Erase::validate(ValidationLogger& validation_logger) const
{
    if (lang::Type::checkMismatch<lang::Variable>(variable_, "value", location(), validation_logger)) return;

    if (!erased_)
    {
        validation_logger.logError("Cannot erase variable '" + variable_->name() + "' which is declared in outer scope",
                                   location());
        return;
    }
}

Statements Erase::expandWith(Expressions, Statements, lang::Context& new_context) const
{
    Statements statements;

    statements.emplace_back(makeOwned<Erase>(variable_->getUndefinedClone<lang::Variable>(new_context), location()));

    return statements;
}
