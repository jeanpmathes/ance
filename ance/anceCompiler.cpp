#include "anceCompiler.h"
#include "anceConstants.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

#include "GlobalScope.h"
#include "llvm/IR/Module.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/IR/Verifier.h"

#include "llvm/Bitcode/BitcodeWriter.h"
#include "lld/Common/Driver.h"

anceCompiler::anceCompiler(Application& app) : application(app), ir(context)
{
	module = new llvm::Module(application.GetName(), context);

	llvm::Triple triple(llvm::sys::getDefaultTargetTriple());

	std::string err;
	const llvm::Target* t = llvm::TargetRegistry::lookupTarget(triple.str(), err);

	llvm::Optional<llvm::Reloc::Model> rm;
	rm = llvm::Reloc::Static;

	llvm::Optional<llvm::CodeModel::Model> cm;
	cm = llvm::CodeModel::Large;

	llvm::TargetOptions opt;

	llvm::TargetMachine* tm = t->createTargetMachine(triple.str(), "generic", "", opt, rm, cm, llvm::CodeGenOpt::None);

	llvm::DataLayout dl = tm->createDataLayout();
	module->setDataLayout(dl);
	module->setTargetTriple(triple.str());

	module->addModuleFlag(llvm::Module::Warning, "Debug Info Version", llvm::DEBUG_METADATA_VERSION);

	di = new llvm::DIBuilder(*module);

	proj_file = di->createFile(application.GetProjectFile().filename().string(), application.GetProjectFile().string());
	unit = di->createCompileUnit(llvm::dwarf::DW_LANG_C, proj_file, "ancec-0", false, "", 0);
	code_file = di->createFile(application.GetCodeFile().filename().string(), application.GetCodeFile().string());

	state = new CompileState(&context, module, &ir, di);
	state->application = &application;
	state->unit = unit;
	state->code_file = code_file;
}

void anceCompiler::Compile(const std::filesystem::path& output_dir)
{
	state->ui32 = di->createBasicType("ui32", 32, llvm::dwarf::DW_ATE_unsigned);

	SetupGlobals();

	application.global_scope()->build_variables(context, module, state, ir, di);
	application.global_scope()->BuildFunctionNames(context, module, state, ir, di);
	application.global_scope()->BuildFunctions(context, module, state, ir, di);

	llvm::FunctionType* main_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(context), false);
	llvm::Function* main = module->getFunction("main");

	llvm::FunctionType* exit_type;
	llvm::Function* exit;
	BuildExit(exit_type, exit);

	BuildStart(main_type, main, exit_type, exit);

	di->finalize();

	llvm::verifyModule(*module, &llvm::errs());
	module->print(llvm::outs(), nullptr);

	std::filesystem::path bc_dir = output_dir / "bc";
	std::filesystem::path bin_dir = output_dir / "bin";

	std::filesystem::create_directory(bc_dir);
	std::filesystem::create_directory(bin_dir);

	std::filesystem::path bc = bc_dir / (application.GetName() + ".bc");
	std::ofstream ofs(bc.string());
	ofs.close();

	std::filesystem::path exe = bin_dir / (application.GetName() + ".exe");

	std::error_code ec;
	llvm::raw_fd_ostream os(bc.string(), ec);
	llvm::WriteBitcodeToFile(*module, os);
	os.close();

	LinkModule(bc, exe);
}

void anceCompiler::SetupGlobals()
{
	llvm::ConstantPointerNull* null = llvm::ConstantPointerNull::get(llvm::PointerType::getInt8PtrTy(context));

	new llvm::GlobalVariable(*module, llvm::Type::getInt8PtrTy(context), false, llvm::GlobalValue::LinkageTypes::CommonLinkage, null, ANCE_STD_INPUT_HANDLE);
	new llvm::GlobalVariable(*module, llvm::Type::getInt8PtrTy(context), false, llvm::GlobalValue::LinkageTypes::CommonLinkage, null, ANCE_STD_OUTPUT_HANDLE);
	new llvm::GlobalVariable(*module, llvm::Type::getInt8PtrTy(context), false, llvm::GlobalValue::LinkageTypes::CommonLinkage, null, ANCE_STD_ERROR_HANDLE);
}

void anceCompiler::BuildExit(llvm::FunctionType*& exit_type, llvm::Function*& exit)
{
	llvm::Type* exit_params[] = { llvm::Type::getInt32Ty(context) };
	exit_type = llvm::FunctionType::get(llvm::Type::getVoidTy(context), exit_params, false);
	exit = llvm::Function::Create(exit_type, llvm::GlobalValue::LinkageTypes::PrivateLinkage, "_exit", module);
	exit->getArg(0)->setName("exitcode");

	llvm::BasicBlock* exit_block = llvm::BasicBlock::Create(context, "entry", exit);
	ir.SetInsertPoint(exit_block);

	state->buildnativecall_FreeConsole();
	state->buildnativecall_ExitProcess(exit->getArg(0));

	ir.CreateRetVoid();
}

void anceCompiler::BuildStart(llvm::FunctionType* main_type, llvm::Function* main, llvm::FunctionType* exit_type, llvm::Function* exit)
{
	llvm::FunctionType* start_type = llvm::FunctionType::get(llvm::Type::getVoidTy(context), false);
	llvm::Function* start = llvm::Function::Create(start_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "_start", module);

	llvm::BasicBlock* start_block = llvm::BasicBlock::Create(context, "entry", start);
	llvm::BasicBlock* alloc_block = llvm::BasicBlock::Create(context, "no_console", start);
	llvm::BasicBlock* prep_block = llvm::BasicBlock::Create(context, "prep", start);

	ir.SetInsertPoint(start_block);

	llvm::Value* attach_success = state->buildnativecall_AttachConsole(-1); // ATTACH_PARENT_PROCESS
	ir.CreateCondBr(attach_success, prep_block, alloc_block);

	ir.SetInsertPoint(alloc_block);

	state->buildnativecall_AllocConsole();
	ir.CreateBr(prep_block);

	ir.SetInsertPoint(prep_block);

	llvm::GlobalVariable* var = module->getGlobalVariable(ANCE_STD_INPUT_HANDLE);
	llvm::Value* handle = state->buildnativecall_GetStdHandle(-10);
	ir.CreateStore(handle, var);

	var = module->getGlobalVariable(ANCE_STD_OUTPUT_HANDLE);
	handle = state->buildnativecall_GetStdHandle(-11);
	ir.CreateStore(handle, var);

	var = module->getGlobalVariable(ANCE_STD_ERROR_HANDLE);
	handle = state->buildnativecall_GetStdHandle(-12);
	ir.CreateStore(handle, var);

	llvm::CallInst* main_exitcode = ir.CreateCall(main_type, main, llvm::None, "exitcode");

	llvm::Value* exit_args = { main_exitcode };
	ir.CreateCall(exit_type, exit, exit_args);

	ir.CreateRetVoid();
}

void anceCompiler::LinkModule(std::filesystem::path& bc, std::filesystem::path& exe)
{
	std::vector<const char*> args;
	args.push_back("lld");

	args.push_back("/verbose");

	args.push_back("/debug:FULL");

	args.push_back("/machine:x64");
	args.push_back("/subsystem:windows");

	args.push_back("/defaultlib:kernel32");

	args.push_back("/libpath:C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.19041.0\\um\\x64");

	args.push_back("/entry:_start");

	// ! string copy not wanted, but necessary as bc.string().c_str() did not work - string was corrupted after passing it to link.
	// todo a more elegant solution should be found!
	std::string out = "/out:" + exe.string();
	char output[out.size() + 1];
	strcpy(output, out.c_str());

	char input[bc.string().size() + 1];
	strcpy(input, bc.string().c_str());

	args.push_back(output);
	args.push_back(input);

	lld::coff::link(args, false, llvm::outs(), llvm::errs());
}