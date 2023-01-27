#include "AnceLinker.h"

#include <lld/Common/Driver.h>

#include "compiler/Unit.h"
#include "lang/ApplicationVisitor.h"

AnceLinker::AnceLinker(Unit& unit) : unit_(unit) {}

bool AnceLinker::link(std::filesystem::path const& obj, std::filesystem::path const& app)
{
    std::vector<char const*> args;
    args.push_back("lld");

    if (unit_.getOptimizationLevel().getDebugEmissionKind() == llvm::DICompileUnit::DebugEmissionKind::FullDebug)
    {
        args.push_back("/debug:FULL");
    }

    if (unit_.getTargetTriple().isArch64Bit()) { args.push_back("/machine:x64"); }

    std::string const os = std::string(unit_.getTargetTriple().getOSName());
    unit_.getType().addLinkerArguments(args, os);

    std::string const out = "/out:" + app.string();
    args.push_back(out.c_str());

    std::string const out_lib = "/implib:" + (app.parent_path() / (app.stem().string() + ".lib")).string();
    args.push_back(out_lib.c_str());

    std::vector<std::string> export_functions;
    for (auto const& export_function : unit_.getExportedFunctions())
    {
        export_functions.push_back("/export:" + export_function);
        args.push_back(export_functions.back().c_str());
    }

    std::filesystem::path const target_data_directory =
        std::filesystem::current_path() / "resources" / "targets" / unit_.getTargetTriple().getTriple();

    if (unit_.isUsingRuntime()
        && !(std::filesystem::exists(target_data_directory) && std::filesystem::is_directory(target_data_directory)))
    {
        std::cout << "ance: build: no target resources found [ " << unit_.getTargetTriple().getTriple() << " ]"
                  << std::endl;
        return false;
    }

    std::vector<std::string> lib_paths;

    if (unit_.isUsingRuntime()) { lib_paths.push_back("/libpath:" + target_data_directory.string()); }

    for (auto const& libpath : unit_.getLibraryPaths()) { lib_paths.push_back("/libpath:" + libpath); }
    for (auto const& libpath : lib_paths) { args.push_back(libpath.c_str()); }

    std::vector<std::string> libs;

    if (unit_.isUsingRuntime()) { libs.emplace_back("/defaultlib:runtime"); }

    for (auto const& lib : unit_.getLibraries()) { libs.push_back("/defaultlib:" + lib); }
    for (auto const& lib : libs) { args.push_back(lib.c_str()); }

    std::string const in = obj.string();
    args.push_back(in.c_str());

    return lld::mingw::link(args, llvm::outs(), llvm::errs(), false, false);
}
