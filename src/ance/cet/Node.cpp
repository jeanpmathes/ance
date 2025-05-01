#include "Node.h"

ance::cet::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::cet::Unit::Unit() : Node(core::Location::global()) {}

ance::cet::BasicBlock::BasicBlock(size_t const number, utility::List<utility::Owned<Statement>> content, utility::Owned<Link> connection, core::Location const& source_location)
    : Node(source_location)
    , id(number)
    , statements(std::move(content))
    , link(std::move(connection))
{}

ance::cet::Return::Return(core::Location const& source_location) : Node(source_location), Link() {}

ance::cet::Branch::Branch(utility::Owned<Expression> expression, BasicBlock const& true_link, BasicBlock const& false_link, core::Location const& source_location)
    : Node(source_location)
    , Link()
    , condition(std::move(expression))
    , true_branch(true_link)
    , false_branch(false_link)
{}

ance::cet::Jump::Jump(BasicBlock const& link, core::Location const& source_location)
    : Node(source_location), Link(), target(link)
{

}

ance::cet::Independent::Independent(utility::Owned<Expression> independent_expression,
                                    core::Location const&      source_location)
    : Node(source_location), Statement(), expression(std::move(independent_expression))
{}

ance::cet::Let::Let(core::Variable const& identifier, utility::Optional<utility::Owned<Expression>> definition, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , variable(identifier)
    , value(std::move(definition))
{}

ance::cet::Assignment::Assignment(core::Variable const& assigned, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , variable(assigned)
    , value(std::move(expression))
{}

ance::cet::Intrinsic::Intrinsic(core::Intrinsic const& used, core::Location const& source_location)
    : Node(source_location), Expression(), intrinsic(used)
{}

ance::cet::Access::Access(core::Variable const& accessed, core::Location const& source_location) : Node(source_location), Expression(), variable(accessed) {}

ance::cet::Constant::Constant(bool const constant, core::Location const& source_location) : Node(source_location), Expression(), value(constant) {}

ance::cet::UnaryOperation::UnaryOperation(core::UnaryOperator const& kind, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location), Expression(), op(kind), operand(std::move(expression))
{}
