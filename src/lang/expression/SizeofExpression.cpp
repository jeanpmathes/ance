#include "SizeofExpression.h"

#include "lang/type/SizeType.h"
#include "lang/type/Type.h"
#include "compiler/CompileContext.h"

SizeofExpression::SizeofExpression(std::unique_ptr<Expression> expression, lang::Location location)
    : Expression(location)
    , expression_(std::move(expression))
{
    addChild(*expression_);
}

Expression& SizeofExpression::expression() const
{
    return *expression_;
}

void SizeofExpression::setScope(lang::Scope* scope)
{
    expression_->setContainingScope(scope);
}

void SizeofExpression::walkDefinitions()
{
    expression_->walkDefinitions();
}

lang::ResolvingHandle<lang::Type> SizeofExpression::type()
{
    return lang::SizeType::getSize();
}

bool SizeofExpression::validate(ValidationLogger& validation_logger)
{
    return expression_->validate(validation_logger);
}

std::shared_ptr<lang::Value> SizeofExpression::getValue() const
{
    return return_value_;
}

llvm::Value* SizeofExpression::buildNativeValue(CompileContext* context)
{
    return lang::SizeType::buildValue(expression_->type()->getContentSize(context->module()));
}
