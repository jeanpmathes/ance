#include "Node.h"

#include <utility>

ance::est::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::est::File::File(utility::List<utility::Owned<Declaration>> declaration_list, core::Location const& source_location)
    : Node(source_location)
    , declarations(std::move(declaration_list))
{}

ance::est::RunnableDeclaration::RunnableDeclaration(utility::Owned<Statement> body_statement, core::Location const& source_location)
    : Node(source_location)
    , Declaration()
    , body(std::move(body_statement))
{}

std::string ance::est::RunnableDeclaration::displayName() const
{
    return "runnable";
}

ance::est::VariableDeclaration::VariableDeclaration(core::AccessModifier                          access,
                                                    core::ExecutionModifier                       execution,
                                                    core::Identifier const&                       name,
                                                    utility::Owned<Expression>                    t,
                                                    core::Assigner                                assignment,
                                                    utility::Optional<utility::Owned<Expression>> definition,
                                                    core::Location const&                         source_location)
    : Node(source_location)
    , Declaration()
    , access_modifier(access)
    , execution_modifier(execution)
    , identifier(name)
    , type(std::move(t))
    , assigner(assignment)
    , value(std::move(definition))
{}

std::string ance::est::VariableDeclaration::displayName() const
{
    return std::string(identifier.text());
}

bool ance::est::Statement::isCompound() const
{
    return false;
}

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

ance::est::Assignment::Assignment(utility::Owned<Expression> left,
                                  core::Assigner const       assignment,
                                  utility::Owned<Expression> right,
                                  core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , assignee(std::move(left))
    , assigner(assignment)
    , value(std::move(right))
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

ance::est::Match::Match(utility::Owned<Expression> expression, utility::List<utility::Owned<MatchCase>> case_list, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , value(std::move(expression))
    , cases(std::move(case_list))
{}

ance::est::Return::Return(utility::Optional<utility::Owned<Expression>> expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , value(std::move(expression))
{}

ance::est::Let::Let(core::Identifier const&                       name,
                    utility::Owned<Expression>                    t,
                    core::Assigner                                assignment,
                    utility::Optional<utility::Owned<Expression>> definition,
                    core::Location const&                         source_location)
    : Node(source_location)
    , Statement()
    , identifier(name)
    , type(std::move(t))
    , assigner(assignment)
    , value(std::move(definition))
{}

ance::est::Erase::Erase(core::Identifier const& name, core::Location const& source_location) : Node(source_location), Statement(), identifier(name) {}

ance::est::Assert::Assert(utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , condition(std::move(expression))
{}

ance::est::ErrorExpression::ErrorExpression(core::Location const& source_location) : Node(source_location), Expression() {}

ance::est::Intrinsic::Intrinsic(utility::Owned<Expression>                intrinsic_name,
                                utility::List<utility::Owned<Expression>> argument_list,
                                core::Location const&                     source_location)
    : Node(source_location)
    , Expression()
    , name(std::move(intrinsic_name))
    , arguments(std::move(argument_list))
{}

ance::est::BlockExpression::BlockExpression(utility::List<utility::Owned<Statement>> statement_list,
                                            utility::Owned<Expression>               expression,
                                            core::Location const&                    source_location)
    : Node(source_location)
    , Expression()
    , statements(std::move(statement_list))
    , result(std::move(expression))
{}

ance::est::Parenthesis::Parenthesis(utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , contained(std::move(expression))
{}

ance::est::Call::Call(utility::Owned<Expression> callable, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , callee(std::move(callable))
    , arguments(std::move(expressions))
{}

ance::est::FunctionConstructor::FunctionConstructor(core::Identifier const&    identifier,
                                                    utility::List<Parameter>   params,
                                                    utility::Owned<Expression> type,
                                                    utility::Owned<Statement>  statement,
                                                    core::Location const&      source_location)
    : Node(source_location)
    , Expression()
    , name(identifier)
    , parameters(std::move(params))
    , return_type(std::move(type))
    , body(std::move(statement))
{}

ance::est::Access::Access(core::Identifier const& ident, core::Location const& source_location) : Node(source_location), Expression(), identifier(ident) {}

ance::est::UnitLiteral::UnitLiteral(core::Location const& source_location) : Node(source_location), Expression() {}

ance::est::SizeLiteral::SizeLiteral(std::string text, core::Location const& source_location) : Node(source_location), Expression(), value(std::move(text)) {}

ance::est::FloatingPointLiteral::FloatingPointLiteral(core::Precision const kind, std::string text, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , precision(kind)
    , value(std::move(text))
{}

ance::est::StringLiteral::StringLiteral(std::string text, core::Location const& source_location) : Node(source_location), Expression(), value(std::move(text))
{}

ance::est::BoolLiteral::BoolLiteral(bool const v, core::Location const& source_location) : Node(source_location), Expression(), value(v) {}

ance::est::Default::Default(utility::Owned<Expression> t, core::Location const& source_location) : Node(source_location), Expression(), type(std::move(t)) {}

ance::est::Here::Here(core::Location const& source_location) : Node(source_location), Expression() {}

ance::est::UnaryOperation::UnaryOperation(core::UnaryOperator const& kind, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , op(kind)
    , operand(std::move(expression))
{}

ance::est::BinaryOperation::BinaryOperation(utility::Owned<Expression> lhs,
                                            core::BinaryOperator       kind,
                                            utility::Owned<Expression> rhs,
                                            core::Location const&      source_location)
    : Node(source_location)
    , Expression()
    , left(std::move(lhs))
    , op(kind)
    , right(std::move(rhs))
{}

ance::est::TypeOf::TypeOf(utility::List<utility::Owned<Expression>> expression_list, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , expressions(std::move(expression_list))
{}
ance::est::MatchCase::MatchCase(utility::List<utility::Owned<Expression>> pattern_list,
                                core::Location const&                     default_location,
                                utility::Owned<Statement>                 code,
                                core::Location const&                     source_location)
    : Node(source_location)
    , Auxiliary()
    , patterns(std::move(pattern_list))
    , default_pattern_location(default_location)
    , body(std::move(code))
{}

ance::est::Parameter::Parameter(core::Identifier const& name, utility::Owned<Expression> t, core::Location const& source_location)
    : identifier(name)
    , type(std::move(t))
    , location(source_location)
{}
