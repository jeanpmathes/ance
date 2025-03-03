#include "Node.h"

ance::ret::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::ret::ErrorStatement::ErrorStatement() : Node(core::Location::global()), Statement() {}

ance::ret::Block::Block(utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , statements(std::move(statement_list))
{}

ance::ret::Independent::Independent(utility::Owned<Expression> independent_expression,
                                    core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , expression(std::move(independent_expression))
{}

ance::ret::ErrorExpression::ErrorExpression() : Node(core::Location::global()), Expression() {}

ance::ret::Intrinsic::Intrinsic(core::Intrinsic const& used, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , intrinsic(used)
{}
