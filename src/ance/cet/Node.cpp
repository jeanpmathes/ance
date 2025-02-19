#include "Node.h"

ance::cet::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::cet::Unit::Unit() : Node(core::Location::global()) {}

ance::cet::BasicBlock::BasicBlock(utility::List<utility::Owned<Statement>> content,
                                  core::Location const&                    source_location)
    : Node(source_location)
    , statements(std::move(content))
{}

ance::cet::Independent::Independent(utility::Owned<Expression> independent_expression,
                                    core::Location const&      source_location)
    : Node(source_location), Statement(), expression(std::move(independent_expression))
{}

ance::cet::Intrinsic::Intrinsic(core::Identifier const& callable, core::Location const& source_location)
    : Node(source_location), Expression(), identifier(callable)
{}
