#include "Node.h"

ance::bbt::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::bbt::BasicBlock::BasicBlock(utility::List<utility::Owned<Statement>> content,
                                  core::Location const&                    source_location)
    : Node(source_location)
    , statements(std::move(content))
{}

ance::bbt::ErrorStatement::ErrorStatement() : Node(core::Location::global()), Statement() {}

ance::bbt::Independent::Independent(utility::Owned<Expression> independent_expression,
                                    core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , expression(std::move(independent_expression))
{}

ance::bbt::ErrorExpression::ErrorExpression() : Node(core::Location::global()), Expression() {}

ance::bbt::Intrinsic::Intrinsic(core::Identifier const& callable, core::Location const& source_location) : Node(source_location), Expression(), identifier(callable) {}
