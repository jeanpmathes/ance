#include "CompileState.h"

CompileState::CompileState(llvm::LLVMContext* c, llvm::Module* m, llvm::IRBuilder<>* ir, llvm::DIBuilder* di)
{
	context = c;
	module = m;
	ir_builder = ir;
	di_builder = di;

	// native: AllocConsole (Kernel32)
	allocConsole_type = llvm::FunctionType::get(llvm::Type::getInt1Ty(*context), false);
	allocConsole = llvm::Function::Create(allocConsole_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "AllocConsole", module);

	// native: AttachConsole (Kernel32)
	llvm::Type* attachConsole_params[] = { llvm::Type::getInt32Ty(*context) };
	attachConsole_type = llvm::FunctionType::get(llvm::Type::getInt1Ty(*context), attachConsole_params, false);
	attachConsole = llvm::Function::Create(attachConsole_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "AttachConsole", module);

	// native: FreeConsole (Kernel32)
	freeConsole_type = llvm::FunctionType::get(llvm::Type::getInt1Ty(*context), false);
	freeConsole = llvm::Function::Create(freeConsole_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "FreeConsole", module);

	// native: GetStdHandle (Kernel32)
	llvm::Type* getStdHandle_params[] = { llvm::Type::getInt32Ty(*context) };
	getStdHandle_type = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(*context), getStdHandle_params, false);
	getStdHandle = llvm::Function::Create(getStdHandle_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "GetStdHandle", module);

	// native: WriteFile (Kernel32)
	llvm::Type* writeFile_params[] = { llvm::Type::getInt8PtrTy(*context), llvm::Type::getInt8PtrTy(*context), llvm::Type::getInt32Ty(*context), llvm::Type::getInt32PtrTy(*context), llvm::Type::getInt8PtrTy(*context) };
	writeFile_type = llvm::FunctionType::get(llvm::Type::getInt1Ty(*context), writeFile_params, false);
	writeFile = llvm::Function::Create(writeFile_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "WriteFile", module);

	// native: ExitProcess (Kernel32)
	llvm::Type* exitProcess_params[] = { llvm::Type::getInt32Ty(*context) };
	exitProcess_type = llvm::FunctionType::get(llvm::Type::getVoidTy(*context), exitProcess_params, false);
	exitProcess = llvm::Function::Create(exitProcess_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "ExitProcess", module);
}

llvm::Value* CompileState::buildnativecall_AllocConsole()
{
	llvm::CallInst* ret = ir_builder->CreateCall(allocConsole_type, allocConsole);

	return ret;
}

llvm::Value* CompileState::buildnativecall_AttachConsole(int32_t pid)
{
	llvm::Value* attachConsole_args[] = { llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), pid, true) };
	llvm::CallInst* ret = ir_builder->CreateCall(attachConsole_type, attachConsole, attachConsole_args);

	return ret;
}

llvm::Value* CompileState::buildnativecall_FreeConsole()
{
	llvm::CallInst* ret = ir_builder->CreateCall(freeConsole_type, freeConsole);

	return ret;
}

llvm::Value* CompileState::buildnativecall_GetStdHandle(int32_t nStdHandle)
{
	llvm::Value* getStdHandle_args[] = { llvm::ConstantInt::get(llvm::Type::getInt32Ty(*context), nStdHandle, true) };
	llvm::CallInst* ret = ir_builder->CreateCall(getStdHandle_type, getStdHandle, getStdHandle_args);

	return ret;
}

llvm::Value* CompileState::buildnativecall_WriteFile(llvm::Value* hFile, llvm::Value* lpBuffer, llvm::Value* nNumberOfBytesToWrite, llvm::Value* lpNumberOfBytesWritten, llvm::Value* lpOverlapped)
{
	llvm::Value* writeFile_args[] = { hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped };
	llvm::CallInst* ret = ir_builder->CreateCall(writeFile_type, writeFile, writeFile_args);

	return ret;
}

void CompileState::buildnativecall_ExitProcess(llvm::Value* uExitCode)
{
	llvm::Value* exitProcess_args[] = { uExitCode };
	ir_builder->CreateCall(exitProcess_type, exitProcess, exitProcess_args);
}