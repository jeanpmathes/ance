#include "Node.h"

#include "ance/core/Scope.h"

ance::est::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::est::ErrorStatement::ErrorStatement(core::Location const& source_location) : Node(source_location), Statement() {}

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

ance::est::Let::Let(core::Identifier const&                       name,
                    utility::Optional<utility::Owned<Expression>> definition,
                    core::Location const&                         source_location)
    : Node(source_location)
    , Statement()
    , identifier(name)
    , value(std::move(definition))
{}

ance::est::Assignment::Assignment(core::Identifier const&    assigned,
                                  utility::Owned<Expression> expression,
                                  core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , identifier(assigned)
    , value(std::move(expression))
{

}

ance::est::ErrorExpression::ErrorExpression(core::Location const& source_location) : Node(source_location), Expression() {}

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

ance::est::Literal::Literal(bool const constant, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , value(constant)
{}
