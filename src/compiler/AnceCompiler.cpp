#include "AnceCompiler.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include <llvm/Bitcode/BitcodeWriter.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Verifier.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Passes/PassBuilder.h>
#include <llvm/Support/FileSystem.h>

#include "compiler/ControlFlowGraphPrinter.h"
#include "compiler/SourceTree.h"
#include "compiler/Unit.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/SizeType.h"

AnceCompiler::AnceCompiler(SourceTree& tree, llvm::Triple const& triple)
    : unit_(tree.unit())
    , triple_(triple)
    , module_(tree.unit().getName(), llvm_context_)
    , ir_(llvm_context_)
    , di_(module_)
    , runtime_()
    , context_(unit_, runtime_, llvm_context_, module_, ir_, di_, tree)
{
    module_.setSourceFileName(tree.unit().getProjectFile().filename().string());

    std::string         err;
    llvm::Target const* t = llvm::TargetRegistry::lookupTarget(triple.str(), err);

    llvm::Optional<llvm::Reloc::Model> rm;
    rm = llvm::Reloc::Static;

    llvm::Optional<llvm::CodeModel::Model> cm;
    cm = llvm::CodeModel::Large;

    llvm::TargetOptions const opt;

    target_machine_ = t->createTargetMachine(triple.str(),
                                             "generic",
                                             "",
                                             opt,
                                             rm,
                                             cm,
                                             unit_.getOptimizationLevel().getCodeGenerationOptimizationLevel());

    llvm::DataLayout const dl = target_machine_->createDataLayout();
    unit_.setTargetInfo(triple, dl);

    module_.setDataLayout(dl);
    module_.setTargetTriple(triple.str());

    module_.addModuleFlag(llvm::Module::Warning, "Dwarf Version", llvm::dwarf::DWARF_VERSION);
    module_.addModuleFlag(llvm::Module::Warning, "Debug Info Version", llvm::DEBUG_METADATA_VERSION);
}

void AnceCompiler::compile(std::filesystem::path const& out)
{
    if (unit_.isUsingRuntime()) context_.runtime().init(context_);

    unit_.globalScope().createNativeBacking(context_);
    unit_.globalScope().buildFunctions(context_);

    assert(context_.allDebugLocationsPopped() && "Every setDebugLocation must be ended with a resetDebugLocation!");

    // Print control flow graph.

    if (unit_.isEmittingExtras())
    {
        std::filesystem::path const cfg_path = out.parent_path() / "cfg.gml";
        std::ofstream               cfg_out(cfg_path);
        ControlFlowGraphPrinter     cfg_printer(cfg_out);
        cfg_printer.visit(unit_);
    }

    // Prepare entry and exit functions.

    llvm::Function* init_function  = buildInit();
    llvm::Function* finit_function = buildFinit();

    switch (unit_.getType())
    {
        case UnitResult::EXECUTABLE:
        {
            lang::ResolvingHandle<lang::Function> main = unit_.globalScope().getEntry();
            buildStart(main, init_function, finit_function);

            break;
        }

        case UnitResult::LIBRARY:
        {
            buildLibStart(init_function, finit_function);

            break;
        }

        case UnitResult::PACKAGE:
        {
            buildLibStart(init_function, finit_function);

            break;
        }
    }

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

    auto opt_level = unit_.getOptimizationLevel().getOptimizationLevel();

    if (opt_level == llvm::OptimizationLevel::O0)
    {
        llvm::ModulePassManager pass_manager = pass_builder.buildO0DefaultPipeline(opt_level);
        pass_manager.run(module_, module_analysis_manager);
    }
    else
    {
        llvm::ModulePassManager pass_manager = pass_builder.buildPerModuleDefaultPipeline(opt_level);
        pass_manager.run(module_, module_analysis_manager);
    }

    // Finish up.

    di_.finalize();
    llvm::verifyModule(module_, &llvm::errs());

    // Emit llvm IR to file.

    if (unit_.isEmittingExtras())
    {
        std::error_code      ec;
        llvm::raw_fd_ostream out_stream(out.string(), ec, llvm::sys::fs::OpenFlags::OF_None);

        if (ec) { std::cerr << "IO error while creating IR file stream: " << ec.message() << std::endl; }

        module_.print(out_stream, nullptr);
    }
}

void AnceCompiler::emitObject(std::filesystem::path const& out)
{

    std::error_code      ec;
    llvm::raw_fd_ostream file(out.string(), ec, llvm::sys::fs::OpenFlags::OF_None);

    if (ec) { std::cerr << "IO error while creating object file stream: " << ec.message() << std::endl; }

    llvm::WriteBitcodeToFile(module_, file);

    file.flush();
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

    unit_.globalScope().buildInitialization(context_);

    ir_.CreateRetVoid();
    return init;
}

llvm::Function* AnceCompiler::buildFinit()
{
    llvm::FunctionType* finit_type = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm_context_), false);
    llvm::Function*     finit      = llvm::Function::Create(finit_type,
                                                   llvm::GlobalValue::LinkageTypes::PrivateLinkage,
                                                   getInternalFunctionName("finit"),
                                                   module_);

    llvm::BasicBlock* start_block = llvm::BasicBlock::Create(llvm_context_, "entry", finit);

    ir_.SetInsertPoint(start_block);

    unit_.globalScope().buildFinalization(context_);

    ir_.CreateRetVoid();
    return finit;
}

void AnceCompiler::buildStart(lang::ResolvingHandle<lang::Function> main, llvm::Function* init, llvm::Function* finit)
{
    llvm::FunctionType* start_type = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(llvm_context_),
        {llvm::Type::getInt32Ty(llvm_context_), llvm::Type::getInt8PtrTy(llvm_context_)->getPointerTo()},
        false);
    llvm::Function* start = llvm::Function::Create(start_type,
                                                   llvm::GlobalValue::LinkageTypes::ExternalLinkage,
                                                   WIN_EXE_MAIN_NAME,
                                                   module_);

    start->addFnAttr(llvm::Attribute::AttrKind::UWTable);
    start->setDSOLocal(true);

    llvm::BasicBlock* start_block = llvm::BasicBlock::Create(llvm_context_, "entry", start);

    ir_.SetInsertPoint(start_block);

    ir_.CreateCall(init);

    Optional<Shared<lang::Value>> exitcode = main->buildCall({}, context_);
    assert(exitcode.hasValue());

    ir_.CreateCall(finit);

    exitcode.value()->buildContentValue(context_);
    ir_.CreateRet(exitcode.value()->getContentValue());
}

void AnceCompiler::buildLibStart(llvm::Function* init, llvm::Function* finit)
{
    auto* fn_type = llvm::FunctionType::get(llvm::Type::getVoidTy(llvm_context_), false);
    assert(fn_type == init->getFunctionType());
    assert(fn_type == finit->getFunctionType());

    auto* byte_ptr_type = llvm::Type::getInt8PtrTy(llvm_context_);
    auto* entry_type =
        llvm::StructType::get(llvm_context_,
                              {llvm::Type::getInt32Ty(llvm_context_), fn_type->getPointerTo(), byte_ptr_type});
    auto* array_type = llvm::ArrayType::get(entry_type, 1);

    {
        auto* global_constructors = new llvm::GlobalVariable(module_,
                                                             array_type,
                                                             true,
                                                             llvm::GlobalValue::LinkageTypes::AppendingLinkage,
                                                             nullptr,
                                                             "llvm.global_ctors");

        auto* data = llvm::ConstantArray::get(
            array_type,
            {llvm::ConstantStruct::get(entry_type,
                                       {llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvm_context_), 65535),
                                        init,
                                        llvm::ConstantPointerNull::get(byte_ptr_type)})});

        global_constructors->setInitializer(data);
    }

    {
        auto* global_destructors = new llvm::GlobalVariable(module_,
                                                            array_type,
                                                            true,
                                                            llvm::GlobalValue::LinkageTypes::AppendingLinkage,
                                                            nullptr,
                                                            "llvm.global_dtors");

        auto* data = llvm::ConstantArray::get(
            array_type,
            {llvm::ConstantStruct::get(entry_type,
                                       {llvm::ConstantInt::get(llvm::Type::getInt32Ty(llvm_context_), 65535),
                                        finit,
                                        llvm::ConstantPointerNull::get(byte_ptr_type)})});

        global_destructors->setInitializer(data);
    }
}

std::string AnceCompiler::getInternalFunctionName(std::string const& name)
{
    return name + INTERNAL_FUNCTION_SUFFIX;
}
