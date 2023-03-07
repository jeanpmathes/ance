#include "ExpressionStatement.h"

#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/expression/BuildableExpression.h"

ExpressionStatement::ExpressionStatement(Owned<BuildableExpression> expression, lang::Location location)
    : Statement(location)
    , expression_(std::move(expression))
{
    addSubexpression(*expression_);
}

BuildableExpression const& ExpressionStatement::expression() const
{
    return *expression_;
}

void ExpressionStatement::validate(ValidationLogger& validation_logger) const
{
    expression_->validate(validation_logger);
}

Statements ExpressionStatement::expandWith(Expressions subexpressions, Statements, lang::Context&) const
{
    Statements statements;

    auto* expression = dynamic_cast<BuildableExpression*>(unwrap(std::move(subexpressions[0])));
    assert(expression != nullptr);
    statements.emplace_back(makeOwned<ExpressionStatement>(Owned<BuildableExpression>(*expression), location()));

    return statements;
}

void ExpressionStatement::doBuild(CompileContext& context)
{
    expression_->build(context);
}
