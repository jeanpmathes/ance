#include "Node.h"

ance::ast::Node::Node(core::Location const& source_location) : location(source_location) {}

bool ance::ast::Statement::isCompound() const
{
    return false;
}

ance::ast::ErrorStatement::ErrorStatement(core::Location const& source_location) : Node(source_location), Statement() {}

ance::ast::Block::Block(utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , statements(std::move(statement_list))
{}

bool ance::ast::Block::isCompound() const
{
    return true;
}

ance::ast::Independent::Independent(utility::Owned<Expression> independent_expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , expression(std::move(independent_expression))
{}

ance::ast::Let::Let(core::Identifier const&                       name,
                    utility::Owned<Expression>                           t,
                    utility::Optional<utility::Owned<Expression>> definition,
                    core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , identifier(name)
    , type(std::move(t))
    , value(std::move(definition))
{}

ance::ast::Assignment::Assignment(core::Identifier const& assigned, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , identifier(assigned)
    , value(std::move(expression))
{}

ance::ast::If::If(utility::Owned<Expression>                   expression,
                  utility::Owned<Statement>                    then_part,
                  utility::Optional<utility::Owned<Statement>> else_part,
                  core::Location const&                        source_location)
    : Node(source_location)
    , Statement()
    , condition(std::move(expression))
    , true_part(std::move(then_part))
    , false_part(std::move(else_part))
{}

ance::ast::Loop::Loop(utility::Owned<Statement> statement, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , body(std::move(statement))
{}

ance::ast::Break::Break(core::Location const& source_location) : Node(source_location), Statement() {}

ance::ast::Continue::Continue(core::Location const& source_location) : Node(source_location), Statement() {}

ance::ast::While::While(utility::Owned<Expression> expression, utility::Owned<Statement> statement, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , condition(std::move(expression))
    , body(std::move(statement))
{}

ance::ast::ErrorExpression::ErrorExpression(core::Location const& source_location) : Node(source_location), Expression() {}

ance::ast::Call::Call(core::Identifier const& callable, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , identifier(callable)
    , arguments(std::move(expressions))
{}

ance::ast::Access::Access(core::Identifier const& accessed, core::Location const& source_location) : Node(source_location), Expression(), identifier(accessed)
{}

ance::ast::Literal::Literal(utility::Shared<core::Value> literal, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , value(std::move(literal))
{}

ance::ast::UnaryOperation::UnaryOperation(core::UnaryOperator const& kind, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , op(kind)
    , operand(std::move(expression))
{}
