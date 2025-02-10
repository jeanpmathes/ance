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
