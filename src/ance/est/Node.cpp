#include "Node.h"

#include "ance/core/Scope.h"

ance::est::Node::Node(core::Location const& source_location) : location(source_location) {}

bool ance::est::Statement::isCompound() const { return false; }

ance::est::ErrorStatement::ErrorStatement(core::Location const& source_location) : Node(source_location), Statement() {}

ance::est::Block::Block(utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , statements(std::move(statement_list))
{}

bool ance::est::Block::isCompound() const
{
    return true;
}

ance::est::Independent::Independent(utility::Owned<Expression> independent_expression,
                                    core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , expression(std::move(independent_expression))
{}

ance::est::Let::Let(core::Identifier const&                       name,
                    utility::Optional<utility::Owned<Expression>> definition,
                    core::Location const&                         source_location)
    : Node(source_location)
    , Statement()
    , identifier(name)
    , value(std::move(definition))
{}

ance::est::Assignment::Assignment(core::Identifier const& assigned, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , identifier(assigned)
    , value(std::move(expression))
{}

ance::est::If::If(utility::Owned<Expression> expression,
                  utility::Owned<Statement>  then_block,
                  utility::Owned<Statement>  else_block,
                  core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , condition(std::move(expression))
    , true_block(std::move(then_block))
    , false_block(std::move(else_block))
{}

ance::est::Loop::Loop(utility::Owned<Statement> statement, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , body(std::move(statement))
{}

ance::est::Break::Break(core::Location const& source_location) : Node(source_location), Statement() {}

ance::est::Continue::Continue(core::Location const& source_location) : Node(source_location), Statement() {}

ance::est::ErrorExpression::ErrorExpression(core::Location const& source_location) : Node(source_location), Expression() {}

ance::est::Call::Call(core::Identifier const& callable, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , identifier(callable)
    , arguments(std::move(expressions))
{}

ance::est::Access::Access(core::Identifier const& accessed, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , identifier(accessed)
{}

ance::est::Literal::Literal(bool const constant, core::Location const& source_location) : Node(source_location), Expression(), value(constant) {}

ance::est::UnaryOperation::UnaryOperation(core::UnaryOperator const& kind, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , op(kind)
    , operand(std::move(expression))
{}
