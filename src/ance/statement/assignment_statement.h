#include "Statement.h"

class Expression;

class assignment_statement : public Statement
{
public:
	assignment_statement(ance::Function* function, unsigned int l, unsigned int c, std::string variable_identifier, Expression* assigned);
	void build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di);
	~assignment_statement();

private:
	std::string variable_identifier_;
	Expression* assigned_;
};
