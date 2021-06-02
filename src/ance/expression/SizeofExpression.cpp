#include "SizeofExpression.h"

#include "CompileState.h"
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

ance::Type* SizeofExpression::getType()
{
	return ance::SizeType::get();
}

ance::Value* SizeofExpression::getValue()
{
	return return_value_;
}

llvm::Value* SizeofExpression::build(
	llvm::LLVMContext&,
	llvm::Module* m,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	return ance::SizeType::buildValue(expression_->getType()->getSize(m));
}