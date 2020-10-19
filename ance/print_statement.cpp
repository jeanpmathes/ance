#include "print_statement.h"

print_statement::print_statement(unsigned int l, unsigned int c) : Statement(c, l)
{
}

void print_statement::build(llvm::LLVMContext& c, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di, llvm::Function* func)
{
}

print_statement::~print_statement()
{
}