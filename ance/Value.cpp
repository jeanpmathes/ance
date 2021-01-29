#include "Value.h"

#include "Expression.h"
#include "CompileState.h"

ance::Value::Value(Expression* expression) : expression_(expression)
{
}

ance::Type* ance::Value::get_type()
{
	return expression_->get_type();
}

llvm::Value* ance::Value::get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return expression_->build(c, m, state, ir, di);
}