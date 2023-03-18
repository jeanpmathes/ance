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

    std::string const resource_data_directory_name       = "ANCE_RESOURCE_DATA_DIRECTORY";
    char const*       resource_data_directory_path_value = std::getenv(resource_data_directory_name.c_str());

    if (resource_data_directory_path_value == nullptr)
    {
        std::cout << "ance: build: no resource data directory set"
                  << " (" << resource_data_directory_name << ")" << std::endl;

        return false;
    }

    std::filesystem::path const resource_data_directory = resource_data_directory_path_value;

    std::filesystem::path const target_data_directory =
        resource_data_directory / "targets" / unit_.getTargetTriple().getTriple();

    if (unit_.isUsingRuntime()
        && !(std::filesystem::exists(target_data_directory) && std::filesystem::is_directory(target_data_directory)))
    {
        std::cout << "ance: build: no target resources found [ " << unit_.getTargetTriple().getTriple() << " ]"
                  << std::endl;

        return false;
    }

    std::vector<std::string> binary_dependencies = unit_.getBinaryDependencyPaths();

    if (unit_.isUsingRuntime())
    {
        UnitResult const            runtime_type = UnitResult::LIBRARY;
        std::string const           runtime_file = "runtime" + runtime_type.getExtension(unit_.getTargetTriple());
        std::filesystem::path const runtime_path = target_data_directory / runtime_file;
        binary_dependencies.push_back(runtime_path.string());
    }

    for (auto const& binary_dependency : binary_dependencies)
    {
        if (!std::filesystem::exists(binary_dependency))
        {
            std::cout << "ance: build: cannot find binary dependency: " << binary_dependency << std::endl;
            return false;
        }

        std::filesystem::path const from = binary_dependency;
        std::filesystem::path const to   = app.parent_path() / from.filename();

        std::filesystem::copy_file(from, to, std::filesystem::copy_options::update_existing);
    }

    std::vector<std::string> lib_paths;

    if (unit_.isUsingRuntime()) { lib_paths.push_back("/libpath:" + target_data_directory.string()); }

    for (auto const& libpath : unit_.getLibraryPaths()) { lib_paths.push_back("/libpath:" + libpath); }
    for (auto const& libpath : lib_paths) { args.push_back(libpath.c_str()); }

    std::vector<std::string> libs;

    if (unit_.isUsingRuntime()) { libs.emplace_back("/defaultlib:runtime"); }

    for (auto const& lib : unit_.getLibraries()) { libs.push_back("/defaultlib:" + lib); }
    for (auto const& lib : libs) { args.push_back(lib.c_str()); }

    if (unit_.isIncludingWholeArchive()) { args.push_back("/wholearchive"); }

    std::string const in = obj.string();
    args.push_back(in.c_str());

    return lld::mingw::link(args, llvm::outs(), llvm::errs(), false, false);
}
