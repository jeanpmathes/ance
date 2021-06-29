#include "CompileState.h"

CompileState::CompileState(llvm::LLVMContext* c, llvm::Module* m, llvm::IRBuilder<>* ir, llvm::DIBuilder* di)
{
	context_ = c;
	module_ = m;
	ir_builder_ = ir;
	di_builder_ = di;
}