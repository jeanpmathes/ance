#include "Node.h"

#include <sstream>
#include <iomanip>

#include "ance/core/Scope.h"
#include "ance/core/Type.h"
#include "ance/core/Intrinsic.h"
#include "ance/core/Function.h"
#include "ance/core/Value.h"

ance::ret::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::ret::ErrorStatement::ErrorStatement(core::Location const& source_location) : Node(source_location), Statement() {}

ance::ret::Block::Block(utility::Owned<core::Scope> own_scope, utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , scope(std::move(own_scope))
    , statements(std::move(statement_list))
{}

ance::ret::Independent::Independent(utility::Owned<Expression> independent_expression,
                                    core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , expression(std::move(independent_expression))
{}

ance::ret::Let::Let(core::Variable const& identifier, utility::Optional<utility::Owned<Expression>> definition, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , variable(identifier)
    , value(std::move(definition))
{}

ance::ret::Assignment::Assignment(core::Variable const& assigned, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , variable(assigned)
    , value(std::move(expression))
{}

ance::ret::If::If(utility::Owned<Expression> expression,
                  utility::Owned<Statement>  then_block,
                  utility::Owned<Statement>  else_block,
                  core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , condition(std::move(expression))
    , true_block(std::move(then_block))
    , false_block(std::move(else_block))
{}

ance::ret::Loop::Loop(utility::Owned<Statement> statement, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , body(std::move(statement))
{}

ance::ret::Break::Break(core::Location const& source_location) : Node(source_location), Statement() {}

ance::ret::Continue::Continue(core::Location const& source_location) : Node(source_location), Statement() {}

ance::ret::Temporary::Temporary(core::Type const& t, utility::Optional<utility::Owned<Expression>> expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , type(t)
    , definition(std::move(expression))
{}

std::string ance::ret::Temporary::id() const
{
    std::ostringstream oss;
    oss << std::hex << std::uppercase << std::setw(12) << std::setfill('0') << reinterpret_cast<std::uintptr_t>(this);
    return oss.str();
}

ance::ret::WriteTemporary::WriteTemporary(Temporary const& target, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , temporary(target)
    , value(std::move(expression))
{}

ance::core::Type const& ance::ret::Expression::type() const
{
    return core::Type::Unit();
}

ance::ret::ErrorExpression::ErrorExpression(core::Location const& source_location) : Node(source_location), Expression() {}

ance::ret::Intrinsic::Intrinsic(core::Intrinsic const& used, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , intrinsic(used)
    , arguments(std::move(expressions))
{}

ance::core::Type const& ance::ret::Intrinsic::type() const
{
    return intrinsic.returnType();
}

ance::ret::Call::Call(core::Function const& function, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , called(function)
    , arguments(std::move(expressions))
{}

ance::core::Type const& ance::ret::Call::type() const
{
    return called.returnType();
}

ance::ret::Access::Access(core::Variable const& accessed, core::Location const& source_location) : Node(source_location), Expression(), variable(accessed) {}

ance::core::Type const& ance::ret::Access::type() const
{
    return variable.type();
}

ance::ret::Constant::Constant(utility::Shared<core::Value> constant, core::Location const& source_location) : Node(source_location), Expression(), value(std::move(constant)) {}

ance::core::Type const& ance::ret::Constant::type() const
{
    return value->type();
}

ance::ret::UnaryOperation::UnaryOperation(core::UnaryOperator const& kind, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , op(kind)
    , operand(std::move(expression))
{}

ance::core::Type const& ance::ret::UnaryOperation::type() const
{
    return core::Type::Bool();
}

ance::ret::ReadTemporary::ReadTemporary(Temporary const& target, core::Location const& source_location) : Node(source_location), Expression(), temporary(target)
{}

ance::core::Type const& ance::ret::ReadTemporary::type() const
{
    return temporary.type;
}
