#include "AnceCompiler.h"

#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>

#include <llvm/Target/TargetMachine.h>
#include <llvm/Support/TargetRegistry.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/Host.h>

#include <llvm/Bitcode/BitcodeWriter.h>
#include <lld/Common/Driver.h>

#include "GlobalScope.h"
#include "SizeType.h"
#include "UnsignedIntegerPointerType.h"

AnceCompiler::AnceCompiler(Application& app)
	: application_(app), ir_(context_)
{
	module_ = new llvm::Module(application_.getName(), context_);

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
	application_.setPointerSize(dl.getPointerSize());
	ance::SizeType::init(context_, app);
	ance::UnsignedIntegerPointerType::init(context_, app);

	module_->setDataLayout(dl);
	module_->setTargetTriple(triple.str());

	module_->addModuleFlag(llvm::Module::Warning, "Debug Info Version", llvm::DEBUG_METADATA_VERSION);

	di_ = new llvm::DIBuilder(*module_);

	proj_file_ =
		di_->createFile(application_.getProjectFile().filename().string(), application_.getProjectFile().string());
	unit_ = di_->createCompileUnit(llvm::dwarf::DW_LANG_C, proj_file_, "ancec-0", false, "", 0);
	code_file_ = di_->createFile(application_.getSourceFile().filename().string(), application_.getSourceFile().string());

	state_ = new CompileContext(&context_, module_, &ir_, di_);
	state_->application_ = &application_;
	state_->unit_ = unit_;
	state_->code_file_ = code_file_;
}

void AnceCompiler::compile(const std::filesystem::path& bc)
{
	state_->runtime_ = new Runtime();
	state_->runtime_->init(context_, module_, state_, ir_, di_);

	state_->ui_32_ = di_->createBasicType("ui32", 32, llvm::dwarf::DW_ATE_unsigned);

	application_.globalScope()->buildVariables(context_, module_, state_, ir_, di_);
	application_.globalScope()->buildFunctionNames(context_, module_, state_, ir_, di_);
	application_.globalScope()->buildFunctions(context_, module_, state_, ir_, di_);

	llvm::FunctionType* main_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(context_), false);
	llvm::Function* main = module_->getFunction("main");

	llvm::FunctionType* exit_type;
	llvm::Function* exit;
	buildExit(exit_type, exit);

	buildStart(main_type, main, exit_type, exit);

	di_->finalize();

	llvm::verifyModule(*module_, &llvm::errs());
	module_->print(llvm::outs(), nullptr);

	std::ofstream ofs(bc.string());
	ofs.close();

	std::error_code ec;
	llvm::raw_fd_ostream os(bc.string(), ec);
	llvm::WriteBitcodeToFile(*module_, os);
	os.close();
}

void AnceCompiler::buildExit(llvm::FunctionType*& exit_type, llvm::Function*& exit)
{
	llvm::Type* exit_params[] = {llvm::Type::getInt32Ty(context_)};
	exit_type = llvm::FunctionType::get(llvm::Type::getVoidTy(context_), exit_params, false);
	exit = llvm::Function::Create(exit_type, llvm::GlobalValue::LinkageTypes::PrivateLinkage, "_exit", module_);

	llvm::Value* exitcode = exit->getArg(0);
	exitcode->setName("exitcode");

	llvm::BasicBlock* exit_block = llvm::BasicBlock::Create(context_, "entry", exit);
	ir_.SetInsertPoint(exit_block);

	llvm::Function* user_exit = module_->getFunction("exit");
	ir_.CreateCall(exit_type, user_exit, {exitcode});

	ir_.CreateRetVoid();
}

void AnceCompiler::buildStart(
	llvm::FunctionType* main_type,
	llvm::Function* main,
	llvm::FunctionType* exit_type,
	llvm::Function* exit
)
{
	llvm::FunctionType* start_type = llvm::FunctionType::get(llvm::Type::getVoidTy(context_), false);
	llvm::Function* start =
		llvm::Function::Create(start_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "_start", module_);

	llvm::BasicBlock* start_block = llvm::BasicBlock::Create(context_, "entry", start);

	ir_.SetInsertPoint(start_block);

	llvm::CallInst* main_exitcode = ir_.CreateCall(main_type, main, llvm::None, "exitcode");

	llvm::Value* exit_args = {main_exitcode};
	ir_.CreateCall(exit_type, exit, exit_args);

	ir_.CreateRetVoid();
}
