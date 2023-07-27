#include "Drop.h"

#include <utility>

#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

Drop::Drop(lang::ResolvingHandle<lang::Variable> variable, lang::Location location)
    : Statement(location)
    , variable_(std::move(variable))
{}

lang::ResolvingHandle<lang::Variable> Drop::variable()
{
    return variable_.as<lang::Variable>().value();
}

lang::Variable const& Drop::variable() const
{
    return *variable_.as<lang::Variable>();
}

void Drop::walkDefinitions()
{
    scope()->registerUsage(variable_);
    dropped_ = scope()->asOrderedScope()->drop(variable_);
}

void Drop::validate(ValidationLogger& validation_logger) const
{
    if (lang::validation::isUndefined(variable_, scope(), location(), validation_logger)) return;
    if (lang::Type::checkMismatch<lang::Variable>(variable_, "value", location(), validation_logger)) return;

    if (!dropped_)
    {
        validation_logger.logError("Cannot drop variable '" + variable_->name() + "' which is declared in outer scope",
                                   location());
        return;
    }
}

Statements Drop::expandWith(Expressions, Statements, lang::Context& new_context) const
{
    Statements statements;

    statements.emplace_back(makeOwned<Drop>(variable_->getUndefinedClone<lang::Variable>(new_context), location()));

    return statements;
}

void Drop::doBuild(CompileContext& context)
{
    auto variable = lang::Type::makeMatching<lang::Variable>(variable_);
    variable->buildFinalization(context);
}
