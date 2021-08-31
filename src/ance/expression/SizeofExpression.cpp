#include "SizeofExpression.h"

#include "ance/construct/value/ExpressionBackedValue.h"
#include "ance/type/SizeType.h"
#include "compiler/CompileContext.h"

SizeofExpression::SizeofExpression(Expression* expression, ance::Location location)
    : BackingExpression(location)
    , expression_(expression)
{}

void SizeofExpression::setScope(ance::Scope* scope)
{
    expression_->setContainingScope(scope);
}

ance::Type* SizeofExpression::type()
{
    return ance::SizeType::get();
}

void SizeofExpression::validate(ValidationLogger& validation_logger)
{
    expression_->validate(validation_logger);
}

ance::Value* SizeofExpression::getValue() const
{
    return return_value_;
}

llvm::Value* SizeofExpression::buildNativeValue(CompileContext* context)
{
    return ance::SizeType::buildValue(expression_->type()->getContentSize(context->module()));
}
