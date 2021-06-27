#include "CompileState.h"

CompileState::CompileState(llvm::LLVMContext* c, llvm::Module* m, llvm::IRBuilder<>* ir, llvm::DIBuilder* di)
{
	context_ = c;
	module_ = m;
	ir_builder_ = ir;
	di_builder_ = di;

	// native: ExitProcess (Kernel32)
	llvm::Type* exitProcess_params[] = {llvm::Type::getInt32Ty(*context_)};
	exit_process_type_ = llvm::FunctionType::get(llvm::Type::getVoidTy(*context_), exitProcess_params, false);
	exit_process_ = llvm::Function::Create(
		exit_process_type_,
		llvm::GlobalValue::LinkageTypes::ExternalLinkage,
		"ExitProcess",
		module_
	);
}

void CompileState::buildnativecall_ExitProcess(llvm::Value* uExitCode) const
{
	llvm::Value* exitProcess_args[] = {uExitCode};
	ir_builder_->CreateCall(exit_process_type_, exit_process_, exitProcess_args);
}