#include "Statement.h"

class Expression;

class print_statement : public Statement
{
public:
	print_statement(ance::Function* function, unsigned int l, unsigned int c, Expression* expression);
	void build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
	~print_statement();

private:
	Expression* expression_;
};
