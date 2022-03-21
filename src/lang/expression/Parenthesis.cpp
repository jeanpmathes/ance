#include "Parenthesis.h"

Parenthesis::Parenthesis(std::unique_ptr<Expression> expression, lang::Location location)
    : Expression(location)
    , expression_(std::move(expression))
{
    addChild(*expression_);
}

Expression& Parenthesis::contained() const
{
    return *expression_;
}

bool Parenthesis::isNamed()
{
    return expression_->isNamed();
}

bool Parenthesis::validate(ValidationLogger& validation_logger)
{
    return expression_->validate(validation_logger);
}

bool Parenthesis::validateAssignment(const std::shared_ptr<lang::Value>& value,
                                     lang::Location                      value_location,
                                     ValidationLogger&                   validation_logger)
{
    return expression_->validateAssignment(value, value_location, validation_logger);
}

lang::ResolvingHandle<lang::Type> Parenthesis::type()
{
    return expression_->type();
}

std::shared_ptr<lang::Value> Parenthesis::getValue() const
{
    return expression_->getValue();
}

void Parenthesis::setScope(lang::Scope* scope)
{
    expression_->setContainingScope(scope);
}

void Parenthesis::walkDefinitions()
{
    expression_->walkDefinitions();
}

void Parenthesis::doAssign(std::shared_ptr<lang::Value> value, CompileContext* context)
{
    expression_->assign(value, context);
}
