#include "CompileContext.h"

CompileContext::CompileContext(llvm::LLVMContext* c, llvm::Module* m, llvm::IRBuilder<>* ir, llvm::DIBuilder* di)
{
	context_ = c;
	module_ = m;
	ir_builder_ = ir;
	di_builder_ = di;
}