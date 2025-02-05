#include "Node.h"

ance::ast::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::ast::ErrorStatement::ErrorStatement() : Node(core::Location::global()), Statement() {}

ance::ast::Block::Block(utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location)
    : Node(source_location),
      Statement()
    , statements(std::move(statement_list))
{}
ance::ast::Independent::Independent(utility::Owned<Expression> independent_expression,
                                    core::Location const&      source_location)
    : Node(source_location), Statement()
    , expression(std::move(independent_expression))
{}

ance::ast::ErrorExpression::ErrorExpression() : Node(core::Location::global()), Expression() {}

ance::ast::Call::Call(core::Identifier const& callable, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , identifier(callable)
{}

void ance::ast::Visitor::visit(ErrorStatement&) {}

void ance::ast::Visitor::visit(Block const& block)
{
    for (auto& statement : block.statements) visit(*statement);
}

void ance::ast::Visitor::visit(Independent const& independent)
{
    visit(*independent.expression);
}

void ance::ast::Visitor::visit(ErrorExpression&) {}

void ance::ast::Visitor::visit(Call const&) {}
