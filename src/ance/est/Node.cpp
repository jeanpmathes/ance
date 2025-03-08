#include "Node.h"

#include "ance/core/Scope.h"

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

ance::est::Let::Let(core::Identifier const& identifier, utility::Optional<utility::Owned<Expression>> definition, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , variable(identifier)
    , value(std::move(definition))
{}

ance::est::ErrorExpression::ErrorExpression() : Node(core::Location::global()), Expression() {}

ance::est::Call::Call(core::Identifier const& callable, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , identifier(callable)
{}

ance::est::Access::Access(core::Identifier const& accessed, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , identifier(accessed)
{}
