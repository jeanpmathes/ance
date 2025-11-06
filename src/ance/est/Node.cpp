#include "Node.h"

#include <sstream>
#include <iomanip>

#include "ance/utility/ID.h"

ance::est::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::est::File::File(utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location)
    : Node(source_location)
    , statements(std::move(statement_list))
{}

bool ance::est::Statement::isCompound() const { return false; }

ance::est::ErrorStatement::ErrorStatement(core::Location const& source_location) : Node(source_location), Statement() {}

ance::est::Pass::Pass(core::Location const& source_location) : Node(source_location), Statement() {}

ance::est::Block::Block(utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , statements(std::move(statement_list))
{}

bool ance::est::Block::isCompound() const
{
    return true;
}

ance::est::Independent::Independent(utility::Owned<Expression> independent_expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , expression(std::move(independent_expression))
{}

ance::est::Write::Write(utility::Owned<Expression> variable, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , target(std::move(variable))
    , value(std::move(expression))
{}

ance::est::If::If(utility::Owned<Expression> expression,
                  utility::Owned<Statement>  then_block,
                  utility::Owned<Statement>  else_block,
                  core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , condition(std::move(expression))
    , true_block(std::move(then_block))
    , false_block(std::move(else_block))
{}

ance::est::Loop::Loop(utility::Owned<Statement> statement, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , body(std::move(statement))
{}

ance::est::Break::Break(core::Location const& source_location) : Node(source_location), Statement() {}

ance::est::Continue::Continue(core::Location const& source_location) : Node(source_location), Statement() {}

ance::est::Temporary::Temporary(utility::Optional<utility::Owned<Expression>> expression,
                                core::Location const&                         source_location)
    : Node(source_location)
    , Statement()
    , definition(std::move(expression))
{}

std::string ance::est::Temporary::id() const
{
    return utility::id(this);
}

ance::est::WriteTemporary::WriteTemporary(Temporary const& target, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , temporary(target)
    , value(std::move(expression))
{}

ance::est::ErrorExpression::ErrorExpression(core::Location const& source_location) : Node(source_location), Expression() {}

ance::est::Intrinsic::Intrinsic(core::Intrinsic const& called, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , intrinsic(called)
    , arguments(std::move(expressions))
{}

ance::est::Call::Call(utility::Owned<Expression> callable, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , called(std::move(callable))
    , arguments(std::move(expressions))
{}

ance::est::Read::Read(utility::Owned<Expression> accessed, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , target(std::move(accessed))
{}

ance::est::UnitLiteral::UnitLiteral(core::Location const& source_location) : Node(source_location), Expression() {}

ance::est::SizeLiteral::SizeLiteral(std::string text, core::Location const& source_location) : Node(source_location), Expression(), value(std::move(text)) {}

ance::est::StringLiteral::StringLiteral(std::string text, core::Location const& source_location) : Node(source_location), Expression(), value(std::move(text))
{}

ance::est::BoolLiteral::BoolLiteral(bool const v, core::Location const& source_location) : Node(source_location), Expression(), value(v) {}

ance::est::TypeLiteral::TypeLiteral(core::Type const& value, core::Location const& source_location) : Node(source_location), Expression(), type(value) {}

ance::est::Default::Default(utility::Owned<Expression> t, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , type(std::move(t))
{}

ance::est::Here::Here(core::Location const& source_location)
    : Node(source_location)
    , Expression()
{}

ance::est::UnaryOperation::UnaryOperation(core::UnaryOperator const& kind, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , op(kind)
    , operand(std::move(expression))
{}

ance::est::ReadTemporary::ReadTemporary(Temporary const& target, core::Location const& source_location) : Node(source_location), Expression(), temporary(target)
{}

ance::est::TypeOf::TypeOf(utility::Owned<Expression> e, core::Location const& source_location) : Node(source_location), Expression(), expression(std::move(e))
{}

ance::est::IdentifierCapture::IdentifierCapture(core::Identifier const& ident, core::Location const& source_location)
    : Node(source_location), Expression(), identifier(ident)
{}

ance::est::CurrentScope::CurrentScope(core::Location const& source_location)
    : Node(source_location)
    , Expression()
{}
