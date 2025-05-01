#include "Node.h"

#include "ance/core/Scope.h"

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

ance::ret::ErrorExpression::ErrorExpression(core::Location const& source_location) : Node(source_location), Expression() {}

ance::ret::Intrinsic::Intrinsic(core::Intrinsic const& used, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , intrinsic(used)
{}

ance::ret::Access::Access(core::Variable const& accessed, core::Location const& source_location) : Node(source_location), Expression(), variable(accessed) {}

ance::ret::Constant::Constant(bool const constant, core::Location const& source_location) : Node(source_location), Expression(), value(constant) {}

ance::ret::UnaryOperation::UnaryOperation(core::UnaryOperator const& kind, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , op(kind)
    , operand(std::move(expression))
{}
