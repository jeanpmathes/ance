#include "anceCompiler.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"
#include "llvm/IR/Verifier.h"

#include "llvm/Bitcode/BitcodeWriter.h"
#include "lld/Common/Driver.h"

void anceCompiler::Compile(Application& application, const std::filesystem::path& output_dir)
{
	llvm::LLVMContext context;
	llvm::Module module("program", context);

	llvm::Triple triple(llvm::sys::getDefaultTargetTriple());

	std::string err;
	const llvm::Target* t = llvm::TargetRegistry::lookupTarget(triple.str(), err);

	llvm::Optional<llvm::Reloc::Model> rm;

	llvm::TargetOptions opt;
	llvm::TargetMachine* tm = t->createTargetMachine(triple.str(), "generic", "", opt, rm, llvm::None, llvm::CodeGenOpt::Default);

	llvm::DataLayout dl = tm->createDataLayout();
	module.setDataLayout(dl);
	module.setTargetTriple(triple.str());

	llvm::IRBuilder<> ir(context);
	llvm::DIBuilder di(module);

	llvm::FunctionType* main_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(context), false);
	llvm::Function* main = llvm::Function::Create(main_type, llvm::GlobalValue::LinkageTypes::PrivateLinkage, "main", module);

	llvm::BasicBlock* main_block = llvm::BasicBlock::Create(context, "entry", main);
	ir.SetInsertPoint(main_block);

	while (application.StatementCount() > 0)
	{
		Statement* statement = application.PopStatement();

		statement->Build(context, ir);

		delete(statement);
	}

	llvm::verifyFunction(*main, &llvm::errs());

	llvm::Type* exit_params[] = { llvm::Type::getInt32Ty(context) };
	llvm::FunctionType* exit_type = llvm::FunctionType::get(llvm::Type::getVoidTy(context), exit_params, false);
	llvm::Function* exit = llvm::Function::Create(exit_type, llvm::GlobalValue::LinkageTypes::PrivateLinkage, "_exit", module);
	exit->getArg(0)->setName("exitcode");

	llvm::BasicBlock* exit_block = llvm::BasicBlock::Create(context, "entry", exit);
	ir.SetInsertPoint(exit_block);

	llvm::Type* exitProcess_params[] = { llvm::Type::getInt32Ty(context) };
	llvm::FunctionType* exitProcess_type = llvm::FunctionType::get(llvm::Type::getVoidTy(context), exitProcess_params, false);
	llvm::Function* exitProcess = llvm::Function::Create(exitProcess_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "ExitProcess", module);

	llvm::Value* exitProcess_args[] = { exit->getArg(0) };
	ir.CreateCall(exitProcess_type, exitProcess, exitProcess_args);

	ir.CreateRetVoid();

	llvm::verifyFunction(*exit, &llvm::errs());

	llvm::FunctionType* start_type = llvm::FunctionType::get(llvm::Type::getVoidTy(context), false);
	llvm::Function* start = llvm::Function::Create(start_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "_start", module);

	llvm::BasicBlock* start_block = llvm::BasicBlock::Create(context, "entry", start);
	ir.SetInsertPoint(start_block);

	llvm::CallInst* main_exitcode = ir.CreateCall(main_type, main, llvm::None, "exitcode");

	llvm::Value* exit_args = { main_exitcode };
	ir.CreateCall(exit_type, exit, exit_args);

	ir.CreateRetVoid();

	llvm::verifyFunction(*start, &llvm::errs());

	llvm::verifyModule(module, &llvm::errs());
	module.print(llvm::outs(), nullptr);

	std::filesystem::path bc_dir = output_dir / "bc";
	std::filesystem::path bin_dir = output_dir / "bin";

	std::filesystem::create_directory(bc_dir);
	std::filesystem::create_directory(bin_dir);

	std::filesystem::path bc = bc_dir / "program.bc";
	std::ofstream ofs(bc.string());
	ofs.close();

	std::filesystem::path exe = bin_dir / "program.exe";
	std::string out = "/out:" + exe.string();

	std::error_code ec;
	llvm::raw_fd_ostream os(bc.string(), ec);
	llvm::WriteBitcodeToFile(module, os);
	os.close();

	std::vector<const char*> args;
	args.push_back("lld");

	args.push_back("/machine:x64");
	args.push_back("/subsystem:windows");

	args.push_back("/defaultlib:kernel32");

	args.push_back("/libpath:C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.19041.0\\um\\x64");

	args.push_back("/entry:_start");

	// ! string copy not wanted, but necessary as bc.string().c_str() did not work - string was corrupted after passing it to link.
	// todo a more elegant solution should be found!
	char input[bc.string().size() + 1];
	strcpy(input, bc.string().c_str());

	char output[out.size() + 1];
	strcpy(output, out.c_str());

	args.push_back(output);
	args.push_back(input);

	lld::coff::link(args, false, llvm::outs(), llvm::errs());
}