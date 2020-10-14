#include "anceCompiler.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

#include "llvm/IR/LLVMContext.h"
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

	llvm::TargetOptions opt;
	llvm::TargetMachine* tm = t->createTargetMachine(triple.str(), "generic", "", opt, rm, llvm::None, llvm::CodeGenOpt::None);

	llvm::DataLayout dl = tm->createDataLayout();
	module->setDataLayout(dl);
	module->setTargetTriple(triple.str());

	module->addModuleFlag(llvm::Module::Warning, "Debug Info Version", llvm::DEBUG_METADATA_VERSION);

	di = new llvm::DIBuilder(*module);

	proj_file = di->createFile(application.GetProjectFile().filename().string(), application.GetProjectFile().string());
	unit = di->createCompileUnit(llvm::dwarf::DW_LANG_C, proj_file, "ancec-0", false, "", 0);
	code_file = di->createFile(application.GetCodeFile().filename().string(), application.GetCodeFile().string());
}

void anceCompiler::Compile(const std::filesystem::path& output_dir)
{
	llvm::DIBasicType* ui32 = di->createBasicType("ui32", 32, llvm::dwarf::DW_ATE_unsigned);

	llvm::FunctionType* main_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(context), false);
	llvm::Function* main = llvm::Function::Create(main_type, llvm::GlobalValue::LinkageTypes::PrivateLinkage, "main", module);

	llvm::SmallVector<llvm::Metadata*, 1> tys;
	tys.push_back(ui32);
	llvm::DISubroutineType* main_type_di = di->createSubroutineType(di->getOrCreateTypeArray(tys));
	llvm::DISubprogram* main_di = di->createFunction(unit, "main", "main", code_file, 0, main_type_di, 0, llvm::DINode::DIFlags::FlagZero, llvm::DISubprogram::toSPFlags(true, true, false, 0U, true));
	main->setSubprogram(main_di);

	BuildApplication(main);

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

	llvm::FunctionType* start_type = llvm::FunctionType::get(llvm::Type::getVoidTy(context), false);
	llvm::Function* start = llvm::Function::Create(start_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "_start", module);

	llvm::BasicBlock* start_block = llvm::BasicBlock::Create(context, "entry", start);
	ir.SetInsertPoint(start_block);

	llvm::CallInst* main_exitcode = ir.CreateCall(main_type, main, llvm::None, "exitcode");

	llvm::Value* exit_args = { main_exitcode };
	ir.CreateCall(exit_type, exit, exit_args);

	ir.CreateRetVoid();

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
	std::filesystem::path pdb = bin_dir / (application.GetName() + ".pdb");

	std::error_code ec;
	llvm::raw_fd_ostream os(bc.string(), ec);
	llvm::WriteBitcodeToFile(*module, os);
	os.close();

	LinkModule(bc, exe, pdb);
}

void anceCompiler::BuildApplication(llvm::Function* main)
{
	llvm::BasicBlock* main_block = llvm::BasicBlock::Create(context, "entry", main);
	ir.SetInsertPoint(main_block);

	while (application.StatementCount() > 0)
	{
		Statement* statement = application.PopStatement();

		ir.SetCurrentDebugLocation(llvm::DILocation::get(context, statement->getLine(), statement->getColumn(), main->getSubprogram()));

		statement->build(context, ir, di, main);

		delete(statement);
	}
}

void anceCompiler::LinkModule(std::filesystem::path& bc, std::filesystem::path& exe, std::filesystem::path& pdb)
{
	std::vector<const char*> args;
	args.push_back("lld");

	args.push_back("/machine:x64");
	args.push_back("/subsystem:windows");

	args.push_back("/defaultlib:kernel32");

	args.push_back("/libpath:C:\\Program Files (x86)\\Windows Kits\\10\\Lib\\10.0.19041.0\\um\\x64");

	args.push_back("/entry:_start");

	args.push_back("/debug");

	// ! string copy not wanted, but necessary as bc.string().c_str() did not work - string was corrupted after passing it to link.
	// todo a more elegant solution should be found!
	std::string out = "/out:" + exe.string();
	char output[out.size() + 1];
	strcpy(output, out.c_str());

	std::string dbg = "/pdb:" + pdb.string();
	char debug[dbg.size() + 1];
	strcpy(debug, dbg.c_str());

	char input[bc.string().size() + 1];
	strcpy(input, bc.string().c_str());

	args.push_back(output);
	/*args.push_back(debug);*/
	args.push_back(input);

	lld::coff::link(args, false, llvm::outs(), llvm::errs());
}