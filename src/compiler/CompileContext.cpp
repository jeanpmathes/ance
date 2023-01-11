#include "CompileContext.h"

#include "compiler/Project.h"
#include "compiler/SourceTree.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/Scope.h"

CompileContext::CompileContext(Unit&              unit,
                               Runtime&           runtime,
                               llvm::LLVMContext& c,
                               llvm::Module&      m,
                               llvm::IRBuilder<>& ir,
                               llvm::DIBuilder&   di,
                               SourceTree&        source_tree)
    : unit_(unit)
    , runtime_(runtime)
    , context_(c)
    , module_(m)
    , ir_builder_(ir)
    , di_builder_(di)
{
    llvm::DIFile* project_file =
        di.createFile(unit_.getProjectFile().filename().generic_string(), unit_.getProjectDirectory().generic_string());

    di_unit_ = di.createCompileUnit(llvm::dwarf::DW_LANG_C, project_file, "ance-000", false, "", 0);

    for (auto& source_file : source_tree.getSourceFiles())
    {
        llvm::DIFile* di_source_file = di.createFile(source_file.get().getFilename().generic_string(),
                                                     source_file.get().getDirectory().generic_string());

        source_files_.emplace_back(di_source_file);
    }
}

Unit& CompileContext::unit()
{
    return unit_;
}

Runtime& CompileContext::runtime()
{
    return runtime_;
}

llvm::LLVMContext& CompileContext::llvmContext()
{
    return context_;
}

llvm::Module& CompileContext::llvmModule()
{
    return module_;
}

llvm::IRBuilder<>& CompileContext::ir()
{
    return ir_builder_;
}

llvm::DIBuilder& CompileContext::di()
{
    return di_builder_;
}

llvm::DICompileUnit& CompileContext::llvmUnit()
{
    return *di_unit_;
}

llvm::DIFile* CompileContext::getSourceFile(lang::Location location)
{
    if (location.isGlobal()) return nullptr;

    return source_files_[location.file()];
}

void CompileContext::setDebugLocation(lang::Location location, lang::Scope& scope)
{
    llvm::DebugLoc const previous_location = ir().getCurrentDebugLocation();
    ir().SetCurrentDebugLocation(location.getDebugLoc(llvmContext(), scope.getDebugScope(*this)));

    debug_loc_stack_.push(previous_location);
}

void CompileContext::resetDebugLocation()
{
    llvm::DebugLoc const previous_location = debug_loc_stack_.top();
    ir().SetCurrentDebugLocation(previous_location);

    debug_loc_stack_.pop();
}

bool CompileContext::allDebugLocationsPopped()
{
    return debug_loc_stack_.empty();
}
