#include "VariableExpression.h"

#include "ExpressionBackedValue.h"
#include "Value.h"
#include "Scope.h"

VariableExpression::VariableExpression(ance::Variable* variable) :
	variable_(variable), value_(new ance::ExpressionBackedValue(this))
{
}

ance::Type* VariableExpression::getType()
{
	return variable_->type();
}

ance::Value* VariableExpression::getValue()
{
	return value_;
}

llvm::Value* VariableExpression::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return variable_->getValue(c, m, state, ir, di);
}

VariableExpression::~VariableExpression() = default;