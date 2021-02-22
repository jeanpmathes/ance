#include "return_statement.h"
#include "Value.h"
#include "VoidType.h"
#include "Function.h"

return_statement::return_statement(ance::Function* function, const unsigned int l, const unsigned int c, ance::Value* return_value) : Statement(function, l, c), return_value_(return_value)
{
}

void return_statement::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	if (return_value_)
	{
		assert(return_value_->get_type() == get_containing_function()->get_return_type());
		ir.CreateRet(return_value_->get_value(c, m, state, ir, di));
	}
	else
	{
		assert(ance::VoidType::get() == get_containing_function()->get_return_type());
		ir.CreateRetVoid();
	}
}

return_statement::~return_statement() = default;