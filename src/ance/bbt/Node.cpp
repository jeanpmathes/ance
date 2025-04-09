#include "Node.h"

ance::bbt::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::bbt::Flow::Flow(utility::List<utility::Owned<BasicBlock>> content, BasicBlock& start, core::Location const& source_location)
    : Node(source_location)
    , blocks(std::move(content))
    , entry(start)
{}

ance::bbt::BasicBlock::BasicBlock(size_t const number, utility::List<utility::Owned<Statement>> content,
utility::Owned<Link> connection,
                                  core::Location const&                    source_location)
    : Node(source_location)
    , id(number)
    , statements(std::move(content))
    , link(std::move(connection))
{}

ance::bbt::ErrorLink::ErrorLink(core::Location const& source_location) : Node(source_location), Link() {}

ance::bbt::Return::Return(core::Location const& source_location) : Node(source_location), Link() {}

ance::bbt::Branch::Branch(utility::Owned<Expression> expression, BasicBlock const& true_link, BasicBlock const& false_link, core::Location const& source_location)
    : Node(source_location)
    , Link()
    , condition(std::move(expression))
    , true_branch(true_link)
    , false_branch(false_link)
{}

ance::bbt::Jump::Jump(BasicBlock const& link, core::Location const& source_location)
    : Node(source_location)
    , Link()
    , target(link)
{}

ance::bbt::ErrorStatement::ErrorStatement(core::Location const& source_location) : Node(source_location), Statement() {}

ance::bbt::Independent::Independent(utility::Owned<Expression> independent_expression,
                                    core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , expression(std::move(independent_expression))
{}

ance::bbt::Let::Let(core::Variable const& identifier, utility::Optional<utility::Owned<Expression>> definition, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , variable(identifier)
    , value(std::move(definition))
{}

ance::bbt::Assignment::Assignment(core::Variable const& assigned, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , variable(assigned)
    , value(std::move(expression))
{}

ance::bbt::ErrorExpression::ErrorExpression(core::Location const& source_location) : Node(source_location), Expression() {}

ance::bbt::Intrinsic::Intrinsic(core::Intrinsic const& used, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , intrinsic(used)
{}

ance::bbt::Access::Access(core::Variable const& accessed, core::Location const& source_location) : Node(source_location), Expression(), variable(accessed) {}

ance::bbt::Constant::Constant(bool constant, core::Location const& source_location) : Node(source_location), Expression(), value(constant) {}
