#include "Node.h"

#include <iomanip>
#include <sstream>

#include "ance/utility/ID.h"

ance::cet::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::cet::Unit::Unit() : Node(core::Location::global()) {}

ance::cet::BasicBlock::BasicBlock(size_t const                             number,
                                  utility::List<utility::Owned<Statement>> content,
                                  utility::Owned<Link>                     connection,
                                  core::Location const&                    source_location)
    : Node(source_location)
    , id(number)
    , statements(std::move(content))
    , link(std::move(connection))
{}

ance::cet::Return::Return(core::Location const& source_location) : Node(source_location), Link() {}

ance::cet::Branch::Branch(Temporary const& temporary, BasicBlock const& true_link, BasicBlock const& false_link, core::Location const& source_location)
    : Node(source_location)
    , Link()
    , condition(temporary)
    , true_branch(true_link)
    , false_branch(false_link)
{}

ance::cet::Jump::Jump(BasicBlock const& link, core::Location const& source_location) : Node(source_location), Link(), target(link) {}

ance::cet::Declare::Declare(core::Variable const& identifier, Temporary const* definition, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , variable(identifier)
    , value(definition)
{}

ance::cet::Store::Store(core::Variable const& assigned, Temporary const& stored, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , variable(assigned)
    , value(stored)
{}

ance::cet::Temporary::Temporary(core::Type const& t, core::Location const& source_location) : Node(source_location), Statement(), type(t) {}

std::string ance::cet::Temporary::id() const
{
    return utility::id(this);
}

ance::cet::CopyTemporary::CopyTemporary(Temporary const& target, Temporary const& value, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , destination(target)
    , source(value)
{}

ance::cet::Intrinsic::Intrinsic(core::Intrinsic const&          used,
                                utility::List<Temporary const*> args,
                                Temporary const&                result,
                                core::Location const&           source_location)
    : Node(source_location)
    , Statement()
    , intrinsic(used)
    , arguments(std::move(args))
    , destination(result)
{}

ance::cet::Call::Call(utility::List<Temporary const*> args, Temporary const& result, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , arguments(std::move(args))
    , destination(result)
{}

ance::cet::Read::Read(core::Variable const& accessed, Temporary const& result, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , variable(accessed)
    , destination(result)
{}

ance::cet::Constant::Constant(utility::Shared<core::Value> constant, Temporary const& result, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , value(constant)
    , destination(result)
{}

ance::cet::UnaryOperation::UnaryOperation(core::UnaryOperator const& kind,
                                          Temporary const&           value,
                                          Temporary const&           result,
                                          core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , op(kind)
    , operand(value)
    , destination(result)
{}
