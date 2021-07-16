#include "SizeofExpression.h"

#include "CompileContext.h"
#include "ExpressionBackedValue.h"
#include "SizeType.h"

SizeofExpression::SizeofExpression(Expression* expression)
    : expression_(expression)
{
}

void SizeofExpression::setScope(ance::Scope* scope)
{
    expression_->setScope(scope);
}

ance::Type* SizeofExpression::type()
{
    return ance::SizeType::get();
}

ance::Value* SizeofExpression::getValue()
{
    return return_value_;
}

llvm::Value* SizeofExpression::buildNativeValue(CompileContext* context)
{
    return ance::SizeType::buildValue(expression_->type()->getContentSize(context->module()));
}