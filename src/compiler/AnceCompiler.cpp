#include "AnceCompiler.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Verifier.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>
#include <llvm/Support/TargetRegistry.h>

#include "ance/scope/GlobalScope.h"
#include "ance/type/SizeType.h"
#include "ance/type/UnsignedIntegerPointerType.h"

AnceCompiler::AnceCompiler(Application& app) : application_(app), ir_(llvm_context_)
{
    module_ = new llvm::Module(application_.getName(), llvm_context_);
    module_->setSourceFileName(application_.getSourceFile().filename().string());

    llvm::Triple triple(llvm::sys::getDefaultTargetTriple());

    std::string         err;
    const llvm::Target* t = llvm::TargetRegistry::lookupTarget(triple.str(), err);

    llvm::Optional<llvm::Reloc::Model> rm;
    rm = llvm::Reloc::Static;

    llvm::Optional<llvm::CodeModel::Model> cm;
    cm = llvm::CodeModel::Large;

    llvm::TargetOptions opt;

    target_machine_ = t->createTargetMachine(triple.str(), "generic", "", opt, rm, cm, llvm::CodeGenOpt::None);

    llvm::DataLayout dl = target_machine_->createDataLayout();
    application_.setPointerSize(dl.getPointerSize());

    ance::SizeType::init(llvm_context_, app);
    ance::UnsignedIntegerPointerType::init(llvm_context_, dl);

    module_->setDataLayout(dl);
    module_->setTargetTriple(triple.str());

    module_->addModuleFlag(llvm::Module::Warning, "Dwarf Version", llvm::dwarf::DWARF_VERSION);
    module_->addModuleFlag(llvm::Module::Warning, "Debug Info Version", llvm::DEBUG_METADATA_VERSION);

    di_ = new llvm::DIBuilder(*module_);

    llvm::DIFile* src_file = di_->createFile(application_.getSourceFile().filename().generic_string(),
                                             application_.getSourceFile().parent_path().generic_string());

    llvm::DICompileUnit* unit = di_->createCompileUnit(llvm::dwarf::DW_LANG_C, src_file, "ancec-0", false, "", 0);

    context_ = new CompileContext(&application_, new Runtime(), &llvm_context_, module_, &ir_, di_, unit, src_file);
}

void AnceCompiler::compile(const std::filesystem::path& out)
{
    context_->runtime()->init(context_);

    application_.globalScope()->createNativeBacking(context_);
    application_.globalScope()->buildFunctions(context_);

    assert(context_->allDebugLocationsPopped() && "Every setDebugLocation must be ended with a resetDebugLocation!");

    llvm::FunctionType* main_type = llvm::FunctionType::get(llvm::Type::getInt32Ty(llvm_context_), false);
    llvm::Function*     main      = module_->getFunction("main");

    llvm::FunctionType* exit_type;
    llvm::Function*     exit;

    buildExit(exit_type, exit);
    buildStart(main_type, main, exit_type, exit);

    di_->finalize();

    llvm::verifyModule(*module_, &llvm::errs());

    // Emit llvm IR to file.

    std::error_code      ec;
    llvm::raw_fd_ostream out_stream(out.string(), ec, llvm::sys::fs::OpenFlags::OF_None);

    if (ec) { std::cerr << "IO error while creating IR file stream: " << ec.message() << std::endl; }

    module_->print(out_stream, nullptr);
}

void AnceCompiler::emitObject(const std::filesystem::path& out)
{
    std::error_code      ec;
    llvm::raw_fd_ostream s(out.string(), ec, llvm::sys::fs::OpenFlags::OF_None);

    if (ec) { std::cerr << "IO error while creating object file stream: " << ec.message() << std::endl; }

    llvm::legacy::PassManager pass;
    auto                      type = llvm::CGFT_ObjectFile;

    if (target_machine_->addPassesToEmitFile(pass, s, nullptr, type))
    {
        std::cerr << "Cannot emit object files for current target." << std::endl;
    }

    pass.run(*module_);
    s.flush();
}

void AnceCompiler::buildExit(llvm::FunctionType*& exit_type, llvm::Function*& exit)
{
    llvm::Type* exit_params[] = {llvm::Type::getInt32Ty(llvm_context_)};
    exit_type                 = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm_context_), exit_params, false);
    exit = llvm::Function::Create(exit_type, llvm::GlobalValue::LinkageTypes::PrivateLinkage, "_exit", module_);

    llvm::Value* exitcode = exit->getArg(0);
    exitcode->setName("exitcode");

    llvm::BasicBlock* exit_block = llvm::BasicBlock::Create(llvm_context_, "entry", exit);
    ir_.SetInsertPoint(exit_block);

    llvm::Function* user_exit = module_->getFunction("exit");
    ir_.CreateCall(exit_type, user_exit, {exitcode});

    ir_.CreateRetVoid();
}

void AnceCompiler::buildStart(llvm::FunctionType* main_type,
                              llvm::Function*     main,
                              llvm::FunctionType* exit_type,
                              llvm::Function*     exit)
{
    llvm::FunctionType* start_type = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm_context_), false);
    llvm::Function*     start =
        llvm::Function::Create(start_type, llvm::GlobalValue::LinkageTypes::ExternalLinkage, "_start", module_);

    llvm::BasicBlock* start_block = llvm::BasicBlock::Create(llvm_context_, "entry", start);

    ir_.SetInsertPoint(start_block);

    llvm::CallInst* main_exitcode = ir_.CreateCall(main_type, main, llvm::None, "exitcode");

    llvm::Value* exit_args = {main_exitcode};
    ir_.CreateCall(exit_type, exit, exit_args);

    ir_.CreateRetVoid();
}
