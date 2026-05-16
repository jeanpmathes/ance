#include "Node.h"

ance::ast::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::ast::File::File(utility::List<utility::Owned<Declaration>> declaration_list, core::Location const& source_location)
    : Node(source_location)
    , ConcreteNode()
    , declarations(std::move(declaration_list))
{}

ance::ast::ErrorDeclaration::ErrorDeclaration(core::Location const& source_location) : Node(source_location), Declaration() {}

ance::ast::RunnableDeclaration::RunnableDeclaration(utility::Owned<Statement> statement, core::Location const& source_location)
    : Node(source_location)
    , Declaration()
    , body(std::move(statement))
{}

ance::ast::VariableDeclaration::VariableDeclaration(core::AccessModifier const                    access,
                                                    core::ExecutionModifier const                 execution,
                                                    core::Identifier const&                       name,
                                                    utility::Owned<Expression>                    t,
                                                    core::Assigner const                          assignment,
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

ance::ast::FunctionDeclaration::FunctionDeclaration(core::AccessModifier const                    access,
                                                    core::ExecutionModifier const                 execution,
                                                    core::Identifier const&                       name,
                                                    utility::List<Parameter>                      params,
                                                    utility::Optional<utility::Owned<Expression>> type,
                                                    utility::Owned<Statement>                     function_body,
                                                    core::Location const&                         source_location)
    : Node(source_location)
    , Declaration()
    , access_modifier(access)
    , execution_modifier(execution)
    , identifier(name)
    , parameters(std::move(params))
    , return_type(std::move(type))
    , body(std::move(function_body))
{}

bool ance::ast::Statement::isCompound() const
{
    return false;
}

ance::ast::ErrorStatement::ErrorStatement(core::Location const& source_location) : Node(source_location), Statement() {}

ance::ast::Block::Block(utility::List<utility::Owned<Statement>> statement_list, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , statements(std::move(statement_list))
{}

bool ance::ast::Block::isCompound() const
{
    return true;
}

ance::ast::Independent::Independent(utility::Owned<Expression> independent_expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , expression(std::move(independent_expression))
{}

ance::ast::Let::Let(core::Identifier const&                       name,
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

ance::ast::Assignment::Assignment(utility::Owned<Expression> left,
                                  core::Assigner             assignment,
                                  utility::Owned<Expression> right,
                                  core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , assignee(std::move(left))
    , assigner(assignment)
    , value(std::move(right))
{}

ance::ast::If::If(utility::Owned<Expression>                   expression,
                  utility::Owned<Statement>                    then_part,
                  utility::Optional<utility::Owned<Statement>> else_part,
                  core::Location const&                        source_location)
    : Node(source_location)
    , Statement()
    , condition(std::move(expression))
    , true_part(std::move(then_part))
    , false_part(std::move(else_part))
{}

ance::ast::Loop::Loop(utility::Owned<Statement> statement, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , body(std::move(statement))
{}

ance::ast::Break::Break(core::Location const& source_location) : Node(source_location), Statement() {}

ance::ast::Continue::Continue(core::Location const& source_location) : Node(source_location), Statement() {}

ance::ast::Return::Return(utility::Optional<utility::Owned<Expression>> expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , value(std::move(expression))
{}

ance::ast::While::While(utility::Owned<Expression> expression, utility::Owned<Statement> statement, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , condition(std::move(expression))
    , body(std::move(statement))
{}

ance::ast::Match::Match(utility::Owned<Expression> expression, utility::List<utility::Owned<MatchCase>> case_list, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , condition(std::move(expression))
    , cases(std::move(case_list))
{}

ance::ast::Erase::Erase(core::Identifier const& name, core::Location const& source_location) : Node(source_location), Statement(), identifier(name) {}

ance::ast::Assert::Assert(utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , condition(std::move(expression))
{}

ance::ast::ErrorExpression::ErrorExpression(core::Location const& source_location) : Node(source_location), Expression() {}

ance::ast::And::And(utility::Owned<Expression> lhs, bool const neg, utility::Owned<Expression> rhs, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , left(std::move(lhs))
    , negated(neg)
    , right(std::move(rhs))
{}

ance::ast::Or::Or(utility::Owned<Expression> lhs, bool const neg, utility::Owned<Expression> rhs, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , left(std::move(lhs))
    , negated(neg)
    , right(std::move(rhs))
{}

ance::ast::Call::Call(utility::Owned<Expression> called, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , callee(std::move(called))
    , arguments(std::move(expressions))
{}

ance::ast::Intrinsic::Intrinsic(utility::Owned<Expression>                intrinsic_name,
                                utility::List<utility::Owned<Expression>> args,
                                core::Location const&                     source_location)
    : Node(source_location)
    , Expression()
    , name(std::move(intrinsic_name))
    , arguments(std::move(args))
{}

ance::ast::TypeOf::TypeOf(utility::List<utility::Owned<Expression>> expression_list, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , expressions(std::move(expression_list))
{}

ance::ast::BlockExpression::BlockExpression(utility::List<utility::Owned<Statement>>      statement_list,
                                            utility::Optional<utility::Owned<Expression>> expression,
                                            core::Location const&                         source_location)
    : Node(source_location)
    , Expression()
    , statements(std::move(statement_list))
    , result(std::move(expression))
{}

ance::ast::Parenthesis::Parenthesis(utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , contained(std::move(expression))
{}

ance::ast::Lambda::Lambda(utility::List<Parameter>                      params,
                          utility::Optional<utility::Owned<Expression>> type,
                          utility::Optional<utility::Owned<Expression>> expression,
                          utility::Optional<utility::Owned<Statement>>  statement,
                          core::Location const&                         source_location)
    : Node(source_location)
    , Expression()
    , parameters(std::move(params))
    , return_type(std::move(type))
    , expression_body(std::move(expression))
    , statement_body(std::move(statement))
{}

ance::ast::Access::Access(core::Identifier const& accessed, core::Location const& source_location) : Node(source_location), Expression(), identifier(accessed)
{}

ance::ast::UnitLiteral::UnitLiteral(core::Location const& source_location) : Node(source_location), Expression() {}

ance::ast::SizeLiteral::SizeLiteral(std::string text, core::Location const& source_location) : Node(source_location), Expression(), value(std::move(text)) {}

ance::ast::FloatingPointLiteral::FloatingPointLiteral(core::Precision const kind, std::string text, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , precision(kind)
    , value(std::move(text))
{}

ance::ast::StringLiteral::StringLiteral(std::string text, core::Location const& source_location) : Node(source_location), Expression(), value(std::move(text))
{}

ance::ast::BoolLiteral::BoolLiteral(bool const v, core::Location const& source_location) : Node(source_location), Expression(), value(v) {}

ance::ast::Here::Here(core::Location const& source_location) : Node(source_location), Expression() {}

ance::ast::UnaryOperation::UnaryOperation(core::UnaryOperator const& kind, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , op(kind)
    , operand(std::move(expression))
{}

ance::ast::BinaryOperation::BinaryOperation(utility::Owned<Expression> lhs,
                                            core::BinaryOperator       kind,
                                            utility::Owned<Expression> rhs,
                                            core::Location const&      source_location)
    : Node(source_location)
    , Expression()
    , left(std::move(lhs))
    , op(kind)
    , right(std::move(rhs))
{}

ance::ast::MatchCase::MatchCase(utility::List<utility::Owned<Expression>> pattern_list,
                                core::Location                            default_location,
                                utility::Owned<Statement>                 code,
                                core::Location const&                     source_location)
    : Node(source_location)
    , Auxiliary()
    , patterns(std::move(pattern_list))
    , default_pattern_location(default_location)
    , body(std::move(code))
{}

ance::ast::MatchExpressionCase::MatchExpressionCase(utility::List<utility::Owned<Expression>> pattern_list,
                                                    core::Location const&                     default_location,
                                                    utility::Owned<Expression>                code,
                                                    core::Location const&                     source_location)
    : Node(source_location)
    , Auxiliary()
    , patterns(std::move(pattern_list))
    , default_pattern_location(default_location)
    , result(std::move(code))
{}

ance::ast::IfExpression::IfExpression(utility::Owned<Expression>                    expression,
                                      utility::Owned<Expression>                    then_part,
                                      utility::Optional<utility::Owned<Expression>> else_part,
                                      core::Location const&                         source_location)
    : Node(source_location)
    , Expression()
    , condition(std::move(expression))
    , then_expression(std::move(then_part))
    , else_expression(std::move(else_part))
{}

ance::ast::MatchExpression::MatchExpression(utility::Owned<Expression>                         expression,
                                            utility::List<utility::Owned<MatchExpressionCase>> case_list,
                                            core::Location const&                              source_location)
    : Node(source_location)
    , Expression()
    , condition(std::move(expression))
    , cases(std::move(case_list))
{}

ance::ast::Parameter::Parameter(core::Identifier const& name, utility::Owned<Expression> t, core::Location const& source_location)
    : identifier(name)
    , type(std::move(t))
    , location(source_location)
{}
