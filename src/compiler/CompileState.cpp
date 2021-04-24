#include "CompileState.h"

CompileState::CompileState(llvm::LLVMContext* c, llvm::Module* m, llvm::IRBuilder<>* ir, llvm::DIBuilder* di)
{
	context_ = c;
	module_ = m;
	ir_builder_ = ir;
	di_builder_ = di;

	// native: AllocConsole (Kernel32)
	alloc_console_type_ = llvm::FunctionType::get(llvm::Type::getInt1Ty(*context_), false);
	alloc_console_ = llvm::Function::Create(
		alloc_console_type_,
		llvm::GlobalValue::LinkageTypes::ExternalLinkage,
		"AllocConsole",
		module_
	);

	// native: AttachConsole (Kernel32)
	llvm::Type* attachConsole_params[] = {llvm::Type::getInt32Ty(*context_)};
	attach_console_type_ = llvm::FunctionType::get(llvm::Type::getInt1Ty(*context_), attachConsole_params, false);
	attach_console_ = llvm::Function::Create(
		attach_console_type_,
		llvm::GlobalValue::LinkageTypes::ExternalLinkage,
		"AttachConsole",
		module_
	);

	// native: FreeConsole (Kernel32)
	free_console_type_ = llvm::FunctionType::get(llvm::Type::getInt1Ty(*context_), false);
	free_console_ = llvm::Function::Create(
		free_console_type_,
		llvm::GlobalValue::LinkageTypes::ExternalLinkage,
		"FreeConsole",
		module_
	);

	// native: GetStdHandle (Kernel32)
	llvm::Type* getStdHandle_params[] = {llvm::Type::getInt32Ty(*context_)};
	get_std_handle_type_ = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*context_), getStdHandle_params, false);
	get_std_handle_ = llvm::Function::Create(
		get_std_handle_type_,
		llvm::GlobalValue::LinkageTypes::ExternalLinkage,
		"GetStdHandle",
		module_
	);

	// native: WriteFile (Kernel32)
	llvm::Type* writeFile_params[] =
		{llvm::Type::getInt8PtrTy(*context_), llvm::Type::getInt8PtrTy(*context_), llvm::Type::getInt32Ty(*context_),
		 llvm::Type::getInt32PtrTy(*context_), llvm::Type::getInt8PtrTy(*context_)};
	write_file_type_ = llvm::FunctionType::get(llvm::Type::getInt1Ty(*context_), writeFile_params, false);
	write_file_ = llvm::Function::Create(
		write_file_type_,
		llvm::GlobalValue::LinkageTypes::ExternalLinkage,
		"WriteFile",
		module_
	);

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

llvm::Value* CompileState::buildnativecall_AllocConsole() const
{
	llvm::CallInst* ret = ir_builder_->CreateCall(alloc_console_type_, alloc_console_);

	return ret;
}

llvm::Value* CompileState::buildnativecall_AttachConsole(int32_t pid) const
{
	llvm::Value* attachConsole_args[] = {llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context_), pid, true)};
	llvm::CallInst* ret = ir_builder_->CreateCall(attach_console_type_, attach_console_, attachConsole_args);

	return ret;
}

llvm::Value* CompileState::buildnativecall_FreeConsole() const
{
	llvm::CallInst* ret = ir_builder_->CreateCall(free_console_type_, free_console_);

	return ret;
}

llvm::Value* CompileState::buildnativecall_GetStdHandle(int32_t nStdHandle) const
{
	llvm::Value* getStdHandle_args[] = {llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context_), nStdHandle, true)};
	llvm::CallInst* ret = ir_builder_->CreateCall(get_std_handle_type_, get_std_handle_, getStdHandle_args);

	return ret;
}

llvm::Value* CompileState::buildnativecall_WriteFile(
	llvm::Value* hFile,
	llvm::Value* lpBuffer,
	llvm::Value* nNumberOfBytesToWrite,
	llvm::Value* lpNumberOfBytesWritten,
	llvm::Value* lpOverlapped
) const
{
	llvm::Value* writeFile_args[] = {hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped};
	llvm::CallInst* ret = ir_builder_->CreateCall(write_file_type_, write_file_, writeFile_args);

	return ret;
}

void CompileState::buildnativecall_ExitProcess(llvm::Value* uExitCode) const
{
	llvm::Value* exitProcess_args[] = {uExitCode};
	ir_builder_->CreateCall(exit_process_type_, exit_process_, exitProcess_args);
}