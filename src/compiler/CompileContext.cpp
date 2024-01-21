#include "CompileContext.h"

#include "compiler/NativeBuild.h"
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
    , execution_(nullptr)
{
    llvm::DIFile* project_file =
        di.createFile(unit_.getProjectFile().filename().generic_string(), unit_.getProjectDirectory().generic_string());

    bool const is_optimized = unit_.getOptimizationLevel().isOptimized();
    auto const debug_kind   = unit_.getOptimizationLevel().getDebugEmissionKind();

    llvm::DICompileUnit* di_unit =
        di.createCompileUnit(llvm::dwarf::DW_LANG_C, project_file, "ance-000", is_optimized, "", 0, "", debug_kind);

    execution_ = std::make_unique<NativeBuild>(*this, c, m, ir, di, di_unit);

    for (auto& source_file : source_tree.getSourceFiles())
    {
        llvm::DIFile* di_source_file = di.createFile(source_file.get().getFilename().generic_string(),
                                                     source_file.get().getDirectory().generic_string());

        SourceFile description = {.path = source_file.get().getRelativePath(), .debug_info = di_source_file};
        source_files_.emplace_back(std::move(description));
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

lang::Context& CompileContext::ctx()
{
    return unit_.globalScope().context();
}

Execution& CompileContext::exec()
{
    return *execution_;
}

llvm::DIFile* CompileContext::getSourceFile(lang::Location location)
{
    if (location.isGlobal()) return nullptr;

    return source_files_[location.file()].debug_info;
}

std::filesystem::path CompileContext::getSourceFilePath(lang::Location location)
{
    if (location.isGlobal()) return {};

    return source_files_[location.file()].path;
}

void CompileContext::setDebugLocation(lang::Location location, lang::Scope& scope)
{
    debug_loc_stack_.push(current_debug_location_);

    exec().ir().SetCurrentDebugLocation(location.getDebugLoc(exec().llvmContext(), exec().llvmScope(scope)));

    current_debug_location_.location    = location;
    current_debug_location_.di_location = exec().ir().getCurrentDebugLocation();
}

void CompileContext::resetDebugLocation()
{
    current_debug_location_ = debug_loc_stack_.top();
    debug_loc_stack_.pop();

    exec().ir().SetCurrentDebugLocation(current_debug_location_.di_location);
}

bool CompileContext::allDebugLocationsPopped()
{
    return debug_loc_stack_.empty();
}

std::string CompileContext::getLocationString()
{
    return current_debug_location_.location.toString(*this);
}
