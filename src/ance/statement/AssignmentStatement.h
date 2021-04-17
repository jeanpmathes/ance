#pragma once
#include "Statement.h"

class Expression;

class AssignmentStatement : public Statement
{
public:
	AssignmentStatement(ance::Function* function, unsigned int l, unsigned int c, std::string variable_identifier, Expression* assigned);
	void build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;
	~AssignmentStatement() override;

private:
	std::string variable_identifier_;
	Expression* assigned_;
};
