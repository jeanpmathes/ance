#include "CompileState.h"

CompileState::CompileState(llvm::LLVMContext* c, llvm::Module* m, llvm::IRBuilder<>* ir, llvm::DIBuilder* di)
{
	context = c;
	module = m;
	ir_builder = ir;
	di_builder = di;

	// native: ExitProcess (Kernel32)
	llvm::Type* exitProcess_params[] = { llvm::Type::getInt32Ty(*context) };
	exitProcess_type = llvm::FunctionType::get(llvm::Type::getVoidTy(*context), exitProcess_params, false);
	exitProcess = llvm::Function::Create(exitProcess_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "ExitProcess", module);
}

void CompileState::buildnativecall_ExitProcess(llvm::Argument* exit_code)
{
	llvm::Value* exitProcess_args[] = { exit_code };
	ir_builder->CreateCall(exitProcess_type, exitProcess, exitProcess_args);
}