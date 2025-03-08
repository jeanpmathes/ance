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

ance::bbt::Let::Let(core::Variable const&                         identifier,
                    utility::Optional<utility::Owned<Expression>> definition,
                    core::Location const&                         source_location)
    : Node(source_location)
    , Statement()
    , variable(identifier)
    , value(std::move(definition))
{}

ance::bbt::ErrorExpression::ErrorExpression() : Node(core::Location::global()), Expression() {}

ance::bbt::Intrinsic::Intrinsic(core::Intrinsic const& used, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , intrinsic(used)
{}

ance::bbt::Access::Access(core::Variable const& accessed, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , variable(accessed)
{}
