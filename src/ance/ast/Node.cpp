#include "Node.h"

#include "ance/core/LiteralType.h"

ance::ast::Node::Node(core::Location const& source_location) : location(source_location) {}

ance::ast::File::File(utility::List<utility::Owned<Declaration>> declaration_list, core::Location const& source_location)
    : Node(source_location)
    , ConcreteNode()
    , declarations(std::move(declaration_list))
{}

ance::ast::ErrorDeclaration::ErrorDeclaration(core::Location const& source_location) : Node(source_location), Declaration()
{

}

ance::ast::RunnableDeclaration::RunnableDeclaration(utility::Owned<Statement> statement, core::Location const& source_location)
    : Node(source_location)
    , Declaration()
    , body(std::move(statement))
{}
ance::ast::VariableDeclaration::VariableDeclaration(core::AccessModifier                          access,
                                                    core::Identifier const&                       name,
                                                    utility::Owned<Expression>                    t,
                                                    core::Assigner                                assignment,
                                                    utility::Optional<utility::Owned<Expression>> definition,
                                                    core::Location const&                         source_location)
    : Node(source_location)
    , Declaration()
    , access_modifier(access)
    , identifier(name)
    , type(std::move(t))
    , assigner(assignment)
    , value(std::move(definition))
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

ance::ast::Assignment::Assignment(core::Identifier const&    assigned,
                                  core::Assigner             assignment,
                                  utility::Owned<Expression> expression,
                                  core::Location const&      source_location)
    : Node(source_location)
    , Statement()
    , identifier(assigned)
    , assigner(assignment)
    , value(std::move(expression))
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

ance::ast::While::While(utility::Owned<Expression> expression, utility::Owned<Statement> statement, core::Location const& source_location)
    : Node(source_location)
    , Statement()
    , condition(std::move(expression))
    , body(std::move(statement))
{}

ance::ast::ErrorExpression::ErrorExpression(core::Location const& source_location) : Node(source_location), Expression() {}

ance::ast::Call::Call(core::Identifier const& callable, utility::List<utility::Owned<Expression>> expressions, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , identifier(callable)
    , arguments(std::move(expressions))
{}

ance::ast::Access::Access(core::Identifier const& accessed, core::Location const& source_location) : Node(source_location), Expression(), identifier(accessed)
{}

ance::ast::UnitLiteral::UnitLiteral(core::Location const& source_location) : Node(source_location), Expression() {}

ance::ast::SizeLiteral::SizeLiteral(std::string text, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , value(std::move(text))
{}

ance::ast::StringLiteral::StringLiteral(std::string text, core::Location const& source_location) : Node(source_location), Expression(), value(std::move(text))
{}

ance::ast::BoolLiteral::BoolLiteral(bool const v, core::Location const& source_location) : Node(source_location), Expression(), value(v)
{}

ance::ast::TypeLiteral::TypeLiteral(core::LiteralType value, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , type(value)
{}

ance::ast::Here::Here(core::Location const& source_location)
    : Node(source_location)
    , Expression()
{}

ance::ast::UnaryOperation::UnaryOperation(core::UnaryOperator const& kind, utility::Owned<Expression> expression, core::Location const& source_location)
    : Node(source_location)
    , Expression()
    , op(kind)
    , operand(std::move(expression))
{}
