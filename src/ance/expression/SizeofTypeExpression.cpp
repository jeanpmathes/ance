#include "SizeofTypeExpression.h"

#include "CompileState.h"
#include "ExpressionBackedValue.h"
#include "SizeType.h"

SizeofTypeExpression::SizeofTypeExpression(ance::Type* type, Application& app)
	: return_value_(new ance::ExpressionBackedValue(this)), return_type_(ance::SizeType::get(app)), type_(type)
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
	return ance::SizeType::get(*state->application_)->buildValue(type_->getSize(m));
}