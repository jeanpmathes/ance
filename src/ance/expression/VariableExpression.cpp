#include "VariableExpression.h"

#include <utility>

#include "ExpressionBackedValue.h"
#include "Value.h"
#include "Scope.h"

VariableExpression::VariableExpression(std::string identifier)
	: identifier_(std::move(identifier)), value_(new ance::ExpressionBackedValue(this))
{
}

void VariableExpression::setScope(ance::Scope* scope)
{
	variable_ = scope->getVariable(identifier_);
}

ance::Type* VariableExpression::getType()
{
	return variable_->type();
}

ance::Value* VariableExpression::getValue()
{
	return value_;
}

llvm::Value* VariableExpression::build(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	return variable_->getValue(c, m, state, ir, di);
}

VariableExpression::~VariableExpression() = default;