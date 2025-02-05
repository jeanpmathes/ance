#include "Node.h"

ance::est::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::est::ErrorStatement::ErrorStatement() : Node(core::Location::global()), Statement() {}

ance::est::Block::Block(utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , statements(std::move(statement_list))
{}

ance::est::Independent::Independent(utility::Owned<Expression> independent_expression,
                                    core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , expression(std::move(independent_expression))
{}

ance::est::ErrorExpression::ErrorExpression() : Node(core::Location::global()), Expression() {}

ance::est::Call::Call(core::Identifier const& callable, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , identifier(callable)
{}
