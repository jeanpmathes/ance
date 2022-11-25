#include "AnceCompiler.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Verifier.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/Host.h>

#include "compiler/Application.h"
#include "compiler/ControlFlowGraphPrinter.h"
#include "compiler/Project.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/SizeType.h"
#include "lang/type/UnsignedIntegerPointerType.h"
#include "lang/utility/Values.h"

AnceCompiler::AnceCompiler(Application& app, SourceTree& tree)
    : application_(app)
    , module_(application_.getProject().getName(), llvm_context_)
    , ir_(llvm_context_)
    , di_(module_)
{
    module_.setSourceFileName(application_.getProject().getProjectFile().filename().string());

    llvm::Triple triple(llvm::sys::getDefaultTargetTriple());

    std::string         err;
    llvm::Target const* t = llvm::TargetRegistry::lookupTarget(triple.str(), err);

    llvm::Optional<llvm::Reloc::Model> rm;
    rm = llvm::Reloc::Static;

    llvm::Optional<llvm::CodeModel::Model> cm;
    cm = llvm::CodeModel::Large;

    llvm::TargetOptions opt;

    target_machine_ = t->createTargetMachine(triple.str(), "generic", "", opt, rm, cm, llvm::CodeGenOpt::None);

    llvm::DataLayout dl = target_machine_->createDataLayout();
    application_.setPointerSize(dl.getPointerSize());

    lang::SizeType::init(llvm_context_, app);
    lang::UnsignedIntegerPointerType::init(llvm_context_, dl);

    module_.setDataLayout(dl);
    module_.setTargetTriple(triple.str());

    module_.addModuleFlag(llvm::Module::Warning, "Dwarf Version", llvm::dwarf::DWARF_VERSION);
    module_.addModuleFlag(llvm::Module::Warning, "Debug Info Version", llvm::DEBUG_METADATA_VERSION);

    llvm::DIFile* project_file = di_.createFile(application_.getProject().getProjectFile().filename().generic_string(),
                                                application_.getProject().getProjectDirectory().generic_string());

    llvm::DICompileUnit* unit = di_.createCompileUnit(llvm::dwarf::DW_LANG_C, project_file, "ance-000", false, "", 0);

    runtime_ = std::make_unique<Runtime>();
    context_ = std::make_unique<CompileContext>(&application_,
                                                runtime_.get(),
                                                &llvm_context_,
                                                &module_,
                                                &ir_,
                                                &di_,
                                                unit,
                                                tree);
}

void AnceCompiler::compile(std::filesystem::path const& out)
{
    context_->runtime()->init(*context_);

    application_.globalScope().createNativeBacking(*context_);
    context_->runtime()->setExit(application_.globalScope().getExit());

    application_.globalScope().buildFunctions(*context_);

    assert(context_->allDebugLocationsPopped() && "Every setDebugLocation must be ended with a resetDebugLocation!");

    // Print control flow graph.

    std::filesystem::path   cfg_path = out.parent_path() / "cfg.gml";
    std::ofstream           cfg_out(cfg_path);
    ControlFlowGraphPrinter cfg_printer(cfg_out);
    cfg_printer.visit(application_);

    // Prepare entry and exit functions.

    lang::ResolvingHandle<lang::Function> main = application_.globalScope().getEntry();

    llvm::Function* init_function = buildInit();
    llvm::Function* exit_function = buildExit();
    buildStart(main, init_function, exit_function);

    llvm::verifyModule(module_, &llvm::errs());

    // Passes.

    llvm::PassBuilder pass_builder(target_machine_);

    llvm::LoopAnalysisManager     loop_analysis_manager;
    llvm::FunctionAnalysisManager function_analysis_manager;
    llvm::CGSCCAnalysisManager    cgscc_analysis_manager;
    llvm::ModuleAnalysisManager   module_analysis_manager;

    pass_builder.registerModuleAnalyses(module_analysis_manager);
    pass_builder.registerFunctionAnalyses(function_analysis_manager);
    pass_builder.registerCGSCCAnalyses(cgscc_analysis_manager);
    pass_builder.registerLoopAnalyses(loop_analysis_manager);
    pass_builder.crossRegisterProxies(loop_analysis_manager,
                                      function_analysis_manager,
                                      cgscc_analysis_manager,
                                      module_analysis_manager);

    auto opt_level = llvm::OptimizationLevel::O1;

    if (opt_level != llvm::OptimizationLevel::O0)
    {
        llvm::ModulePassManager pass_manager =
            pass_builder.buildModuleSimplificationPipeline(opt_level, llvm::ThinOrFullLTOPhase::None);
        pass_manager.run(module_, module_analysis_manager);
    }

    // Finish up.

    di_.finalize();
    llvm::verifyModule(module_, &llvm::errs());

    // Emit llvm IR to file.

    std::error_code      ec;
    llvm::raw_fd_ostream out_stream(out.string(), ec, llvm::sys::fs::OpenFlags::OF_None);

    if (ec) { std::cerr << "IO error while creating IR file stream: " << ec.message() << std::endl; }

    module_.print(out_stream, nullptr);
}

void AnceCompiler::emitObject(std::filesystem::path const& out)
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

    pass.run(module_);
    s.flush();
}

llvm::Function* AnceCompiler::buildInit()
{
    llvm::FunctionType* init_type = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm_context_), false);
    llvm::Function*     init      = llvm::Function::Create(init_type,
                                                  llvm::GlobalValue::LinkageTypes::PrivateLinkage,
                                                  getInternalFunctionName("init"),
                                                  module_);

    llvm::BasicBlock* start_block = llvm::BasicBlock::Create(llvm_context_, "entry", init);

    ir_.SetInsertPoint(start_block);

    application_.globalScope().buildInitialization(*context_);

    ir_.CreateRetVoid();
    return init;
}

llvm::Function* AnceCompiler::buildExit()
{
    lang::ResolvingHandle<lang::Type> exitcode_type = lang::FixedWidthIntegerType::get(32, false);

    llvm::Type*         exit_params[] = {exitcode_type->getContentType(llvm_context_)};
    llvm::FunctionType* exit_type = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm_context_), exit_params, false);
    llvm::Function*     exit      = llvm::Function::Create(exit_type,
                                                  llvm::GlobalValue::LinkageTypes::PrivateLinkage,
                                                  getInternalFunctionName("exit"),
                                                  module_);

    llvm::Value* exitcode = exit->getArg(0);
    exitcode->setName("exitcode");

    llvm::BasicBlock* exit_block = llvm::BasicBlock::Create(llvm_context_, "entry", exit);
    ir_.SetInsertPoint(exit_block);

    lang::ResolvingHandle<lang::Function> user_exit = application_.globalScope().getExit();

    std::vector<std::shared_ptr<lang::Value>> args;
    args.push_back(
        std::make_shared<lang::WrappedNativeValue>(exitcode_type,
                                                   lang::values::contentToNative(exitcode_type, exitcode, *context_)));

    user_exit->buildCall(args, *context_);

    ir_.CreateRetVoid();
    return exit;
}

void AnceCompiler::buildStart(lang::ResolvingHandle<lang::Function> main, llvm::Function* init, llvm::Function* exit)
{
    llvm::FunctionType* start_type = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm_context_), false);
    llvm::Function*     start      = llvm::Function::Create(start_type,
                                                   llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                                                   getInternalFunctionName("start"),
                                                   module_);

    llvm::BasicBlock* start_block = llvm::BasicBlock::Create(llvm_context_, "entry", start);

    ir_.SetInsertPoint(start_block);

    ir_.CreateCall(init);

    std::shared_ptr<lang::Value> exitcode = main->buildCall({}, *context_);
    exitcode->buildContentValue(*context_);

    ir_.CreateCall(exit, {exitcode->getContentValue()});

    ir_.CreateRetVoid();
}

std::string AnceCompiler::getInternalFunctionName(std::string const& name)
{
    return name + INTERNAL_FUNCTION_SUFFIX;
}
