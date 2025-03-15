#include "Node.h"

ance::ast::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::ast::ErrorStatement::ErrorStatement(core::Location const& source_location) : Node(source_location), Statement() {}

ance::ast::Block::Block(utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location)
    : Node(source_location),
      Statement()
    , statements(std::move(statement_list))
{}
ance::ast::Independent::Independent(utility::Owned<Expression> independent_expression,
                                    core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , expression(std::move(independent_expression))
{}

ance::ast::Let::Let(core::Identifier const&                       identifier,
                    utility::Optional<utility::Owned<Expression>> definition,
                    core::Location const&                         source_location)
    : Node(source_location)
    , Statement()
    , variable(identifier)
    , value(std::move(definition))
{}

ance::ast::ErrorExpression::ErrorExpression(core::Location const& source_location) : Node(source_location), Expression() {}

ance::ast::Call::Call(core::Identifier const& callable, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , identifier(callable)
{}

ance::ast::Access::Access(core::Identifier const& accessed, core::Location const& source_location) : Node(source_location), Expression(), identifier(accessed) {}
