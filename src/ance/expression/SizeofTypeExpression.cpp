#include "SizeofTypeExpression.h"

#include "CompileState.h"
#include "ExpressionBackedValue.h"
#include "SizeType.h"

SizeofTypeExpression::SizeofTypeExpression(ance::Type* type)
	: return_value_(new ance::ExpressionBackedValue(this)), return_type_(ance::SizeType::get()), type_(type)
{
}

ance::Type* SizeofTypeExpression::getType()
{
	return return_type_;
}

ance::Value* SizeofTypeExpression::getValue()
{
	return return_value_;
}

llvm::Value* SizeofTypeExpression::build(
	llvm::LLVMContext&,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	return ance::SizeType::get()->buildValue(type_->getSize(m));
}