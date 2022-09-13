#include "Assignment.h"

#include "lang/ApplicationVisitor.h"
#include "lang/Assigner.h"
#include "lang/construct/Function.h"
#include "lang/expression/Expression.h"
#include "validation/ValidationLogger.h"

Assignment::Assignment(std::unique_ptr<Expression> assignable,
                       lang::Assigner              assigner,
                       std::unique_ptr<Expression> assigned,
                       lang::Location              location)
    : Statement(location)
    , assignable_(std::move(assignable))
    , assigner_(assigner)
    , assigned_(std::move(assigned))
{
    assert(assigner != lang::Assigner::REFERENCE_BINDING);

    addSubexpression(*assignable_);
    addSubexpression(*assigned_);
}

Expression& Assignment::assignable() const
{
    return *assignable_;
}

lang::Assigner Assignment::assigner() const
{
    return assigner_;
}

Expression& Assignment::assigned() const
{
    return *assigned_;
}

void Assignment::validate(ValidationLogger& validation_logger) const
{
    if (assigner_.isFinal())
    {
        validation_logger.logError("Assignment to declared variable cannot be final", location());
        return;
    }

    if (assigned_->validate(validation_logger))
    {
        assignable_->validateAssignment(assigned_->getValue(), assigned_->location(), validation_logger);
    }
}

Statements Assignment::expandWith(Expressions subexpressions, Statements) const
{
    Statements statements;

    statements.push_back(std::make_unique<Assignment>(std::move(subexpressions[0]),
                                                      assigner_,
                                                      std::move(subexpressions[1]),
                                                      location()));

    return statements;
}

void Assignment::doBuild(CompileContext& context)
{
    assignable_->assign(assigned_->getValue(), context);
}

