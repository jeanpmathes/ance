#include "variable_expression.h"

#include "Value.h"
#include "Scope.h"

variable_expression::variable_expression(ance::Variable* variable) :
	variable_(variable), value_(new ance::Value(this))
{
}

ance::Type* variable_expression::get_type()
{
	return variable_->type();
}

ance::Value* variable_expression::get_value()
{
	return value_;
}

llvm::Value* variable_expression::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return variable_->get_value(c, m, state, ir, di);
}

variable_expression::~variable_expression() = default;