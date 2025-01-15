#include "Node.h"

ance::ast::Block::Block(utility::List<utility::Owned<Statement>> block_statements)
    : statements(std::move(block_statements))
{}

ance::ast::Independent::Independent(utility::Owned<Expression> independent_expression)
    : expression(std::move(independent_expression))
{}

void ance::ast::Visitor::visit(Block const& block)
{
    for (auto& statement : block.statements) visit(*statement);
}

void ance::ast::Visitor::visit(Independent const& independent)
{
    visit(*independent.expression);
}

void ance::ast::Visitor::visit(Call const&) {}
