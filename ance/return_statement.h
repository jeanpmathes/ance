#include "Statement.h"
class return_statement :
	public Statement
{
public:
	return_statement(unsigned int l, unsigned int c, ance::Value* return_value);
	void build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
	~return_statement();

private:
	ance::Value* return_value_;
};
