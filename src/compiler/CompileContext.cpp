#include "CompileContext.h"

CompileContext::CompileContext(Application* app, Runtime* runtime, llvm::LLVMContext* c, llvm::Module* m, llvm::IRBuilder<>* ir, llvm::DIBuilder* di, llvm::DICompileUnit* unit, llvm::DIFile* code_file) : application_(app), runtime_(runtime), context_(c), module_(m), ir_builder_(ir), di_builder_(di), unit_(unit), code_file_(code_file)
{
}

Application* CompileContext::application()
{
	return application_;
}

Runtime * CompileContext::runtime()
{
	return runtime_;
}

llvm::LLVMContext* CompileContext::context()
{
	return context_;
}

llvm::Module* CompileContext::module()
{
	return module_;
}

llvm::IRBuilder<>* CompileContext::ir()
{
	return ir_builder_;
}

llvm::DIBuilder* CompileContext::di()
{
	return di_builder_;
}

llvm::DICompileUnit* CompileContext::unit()
{
	return unit_;
}

llvm::DIFile * CompileContext::codeFile()
{
	return code_file_;
}
