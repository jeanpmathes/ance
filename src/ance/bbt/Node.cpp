#include "Node.h"

#include <iomanip>

ance::bbt::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::bbt::UnorderedScope::UnorderedScope(utility::List<utility::Owned<Flow>> flow_list, core::Location const& source_location)
    : Node(source_location)
    , flows(std::move(flow_list))
{}

ance::bbt::Flow::Flow(utility::List<utility::Owned<BasicBlock>> content, BasicBlock& start, std::string id, core::Location const& source_location)
    : Node(source_location)
    , blocks(std::move(content))
    , entry(start)
    , identifier(std::move(id))
{}

std::string ance::bbt::Flow::id() const
{
    return identifier;
}

ance::bbt::BasicBlock::BasicBlock(size_t const                             number,
                                  utility::List<utility::Owned<Statement>> content,
                                  utility::Owned<Link>                     connection,
                                  core::Location const&                    source_location)
    : Node(source_location)
    , id(number)
    , statements(std::move(content))
    , link(std::move(connection))
{}

ance::bbt::ErrorLink::ErrorLink(core::Location const& source_location) : Node(source_location), Link() {}

ance::bbt::Return::Return(core::Location const& source_location) : Node(source_location), Link() {}

ance::bbt::Branch::Branch(Temporary const& temporary, BasicBlock const& true_link, BasicBlock const& false_link, core::Location const& source_location)
    : Node(source_location)
    , Link()
    , condition(temporary)
    , true_branch(true_link)
    , false_branch(false_link)
{}

ance::bbt::Jump::Jump(BasicBlock const& link, core::Location const& source_location) : Node(source_location), Link(), target(link) {}

bool ance::bbt::Statement::isRelevantForReachability() const
{
    return true;
}

ance::bbt::ErrorStatement::ErrorStatement(core::Location const& source_location) : Node(source_location), Statement() {}

ance::bbt::Pass::Pass(core::Location const& source_location) : Node(source_location), Statement() {}

ance::bbt::Store::Store(Temporary const& lref, Temporary const& stored, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , target(lref)
    , value(stored)
{}

ance::bbt::Access::Access(Temporary const& var, Temporary const& result, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , variable(var)
    , destination(result)
{}

ance::bbt::Temporary::Temporary(std::string id, core::Location const& source_location) : Node(source_location), Statement(), identifier(std::move(id)) {}

std::string ance::bbt::Temporary::id() const
{
    return std::format("t\"{}\"", identifier);
}

ance::bbt::CopyTemporary::CopyTemporary(Temporary const& target, Temporary const& value, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , destination(target)
    , source(value)
{}

ance::bbt::Intrinsic::Intrinsic(core::Intrinsic                                        used,
                                utility::List<std::reference_wrapper<Temporary const>> args,
                                Temporary const&                                       result,
                                core::Location const&                                  source_location)
    : Node(source_location)
    , Statement()
    , intrinsic(used)
    , arguments(std::move(args))
    , destination(result)
{}

ance::bbt::Call::Call(Temporary const&                                       function,
                      utility::List<std::reference_wrapper<Temporary const>> args,
                      Temporary const&                                       result,
                      core::Location const&                                  source_location)
    : Node(source_location)
    , Statement()
    , called(function)
    , arguments(std::move(args))
    , destination(result)
{}

ance::bbt::AnonymousFunctionConstructor::AnonymousFunctionConstructor(utility::List<Parameter> params,
                                                                      Temporary const&         type,
                                                                      utility::Owned<Flow>     flow,
                                                                      Temporary const&         result,
                                                                      core::Location const&    source_location)
    : Node(source_location)
    , Statement()
    , parameters(std::move(params))
    , return_type(type)
    , body(std::move(flow))
    , destination(result)
{}

ance::bbt::Constant::Constant(utility::Shared<Value> constant, Temporary const& result, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , value(std::move(constant))
    , destination(result)
{}

ance::bbt::Default::Default(Temporary const& t, Temporary const& result, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , type(t)
    , destination(result)
{}

ance::bbt::CurrentScope::CurrentScope(Temporary const& result, core::Location const& source_location) : Node(source_location), Statement(), destination(result)
{}

ance::bbt::UnaryOperation::UnaryOperation(core::UnaryOperator const& kind,
                                          Temporary const&           value,
                                          Temporary const&           result,
                                          core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , op(kind)
    , operand(value)
    , destination(result)
{}

ance::bbt::TypeOf::TypeOf(Temporary const& expr, Temporary const& result, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , expression(expr)
    , destination(result)
{}

ance::bbt::OrderedScopeEnter::OrderedScopeEnter(core::Location const& source_location) : Node(source_location), Statement() {}

bool ance::bbt::OrderedScopeEnter::isRelevantForReachability() const
{
    return false;
}

ance::bbt::OrderedScopeExit::OrderedScopeExit(OrderedScopeEnter const& entry, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , enter(entry)
{}

bool ance::bbt::OrderedScopeExit::isRelevantForReachability() const
{
    return false;
}

ance::bbt::SetReturnValue::SetReturnValue(Temporary const& return_value, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , value(return_value)
{}

ance::bbt::Parameter::Parameter(core::Identifier const& name, Temporary const& t, core::Location const& source_location)
    : identifier(name)
    , type(t)
    , location(source_location)
{}
