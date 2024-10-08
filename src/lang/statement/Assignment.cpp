#include "Assignment.h"

#include "lang/ApplicationVisitor.h"
#include "lang/Assigner.h"
#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "validation/ValidationLogger.h"

Assignment::Assignment(Owned<Expression> assignable,
                       lang::Assigner    assigner,
                       Owned<Expression> assigned,
                       lang::Location    location)
    : Statement(location)
    , assignable_(std::move(assignable))
    , assigner_(assigner)
    , assigned_(std::move(assigned))
{
    assert(assigner != lang::Assigner::REFERENCE_BINDING);

    addSubexpression(*assignable_);
    addSubexpression(*assigned_);
}

Expression const& Assignment::assignable() const
{
    return *assignable_;
}

lang::Assigner Assignment::assigner() const
{
    return assigner_;
}

Expression const& Assignment::assigned() const
{
    return *assigned_;
}

bool Assignment::validate(ValidationLogger& validation_logger) const
{
    if (assigner_.isFinal())
    {
        validation_logger.logError("Assignment to declared variable cannot be final", location());
        return false;
    }

    if (assigned_->validate(validation_logger))
    {
        return assignable_->validateAssignment(assigned_->type(), assigned_->location(), validation_logger);
    }

    return false;
}

Statements Assignment::expandWith(Expressions subexpressions, Statements, lang::Context&) const
{
    Statements statements;

    statements.emplace_back(
        makeOwned<Assignment>(std::move(subexpressions[0]), assigner_, std::move(subexpressions[1]), location()));

    return statements;
}
