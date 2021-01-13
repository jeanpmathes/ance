#include "variable_expression.h"

#include "Value.h"
#include "Scope.h"

variable_expression::variable_expression(ance::Scope* scope, std::string identifier) : scope_(scope), identifier_(identifier), value_(new ance::Value(this))
{
}

ance::Value* variable_expression::get_value()
{
	return value_;
}

llvm::Value* variable_expression::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return scope_->GetConstantOrVariable(identifier_, c, m, state, ir, di);
}

variable_expression::~variable_expression() = default;