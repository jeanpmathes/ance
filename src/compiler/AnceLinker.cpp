#include "AnceLinker.h"

#include <lld/Common/Driver.h>
#include <llvm/Support/CrashRecoveryContext.h>

LLD_HAS_DRIVER(coff)

#include "compiler/Unit.h"
#include "lang/ApplicationVisitor.h"

AnceLinker::AnceLinker(Unit& unit) : unit_(unit) {}

bool AnceLinker::link(std::filesystem::path const& obj, std::filesystem::path const& app, std::ostream& stream)
{
    std::vector<char const*> args;

    args.push_back("lld");

    if (unit_.getOptimizationLevel().getDebugEmissionKind() == llvm::DICompileUnit::DebugEmissionKind::FullDebug)
    {
        args.push_back("/debug:full");
        args.push_back("/debug:dwarf");
    }
    else { args.push_back("/ltcg"); }

    args.push_back("/nologo");
    args.push_back("/errorlimit:0");

    if (unit_.getTarget().is64Bit()) { args.push_back("/machine:x64"); }

    unit_.getType().addLinkerArguments(args, unit_.getTarget());

    std::string const out = "/out:" + app.string();
    args.push_back(out.c_str());

    std::string const out_lib = "/implib:" + (app.parent_path() / (app.stem().string() + ".lib")).string();
    args.push_back(out_lib.c_str());

    std::string const resource_data_directory_name       = "ANCE_RESOURCE_DATA_DIRECTORY";
    char const*       resource_data_directory_path_value = std::getenv(resource_data_directory_name.c_str());

    if (resource_data_directory_path_value == nullptr)
    {
        stream << "ance: build: no resource data directory set"
               << " (" << resource_data_directory_name << ")" << std::endl;

        return false;
    }

    std::filesystem::path const resource_data_directory = resource_data_directory_path_value;

    std::filesystem::path const target_data_directory =
        resource_data_directory / "targets" / unit_.getTarget().toString();

    if (unit_.isUsingRuntime()
        && !(std::filesystem::exists(target_data_directory) && std::filesystem::is_directory(target_data_directory)))
    {
        stream << "ance: build: no target resources found [ " << unit_.getTarget().toString() << " ]" << std::endl;

        return false;
    }

    std::vector<std::string> binary_dependencies = unit_.getBinaryDependencyPaths();

    if (unit_.isUsingRuntime())
    {
        UnitResult const            runtime_type = UnitResult::LIBRARY;
        std::string const           runtime_file = "runtime" + runtime_type.getExtension(unit_.getTarget());
        std::filesystem::path const runtime_path = target_data_directory / runtime_file;
        binary_dependencies.push_back(runtime_path.string());
    }

    for (auto const& binary_dependency : binary_dependencies)
    {
        if (!std::filesystem::exists(binary_dependency))
        {
            stream << "ance: build: cannot find binary dependency: " << binary_dependency << std::endl;
            return false;
        }

        std::filesystem::path const from = binary_dependency;
        std::filesystem::path const to   = app.parent_path() / from.filename();

        std::filesystem::copy_file(from, to, std::filesystem::copy_options::update_existing);
    }

    std::vector<std::string> lib_paths;
    std::vector<std::string> libs;

    bool const ok = getTargetRequirements(libs, lib_paths, stream);
    if (!ok) return false;

    if (unit_.isUsingRuntime()) { lib_paths.push_back("/libpath:" + target_data_directory.string()); }
    if (unit_.isUsingRuntime()) { libs.emplace_back("/defaultlib:runtime"); }

    lib_paths.push_back("/libpath:" + app.parent_path().string());

    for (auto const& libpath : unit_.getLibraryPaths()) { lib_paths.push_back("/libpath:" + libpath); }
    for (auto const& libpath : lib_paths) { args.push_back(libpath.c_str()); }

    for (auto const& lib : unit_.getLibraries()) { libs.push_back("/defaultlib:" + lib); }
    for (auto const& lib : unit_.getLinkDependencies()) { libs.push_back("/defaultlib:" + lib); }
    for (auto const& lib : libs) { args.push_back(lib.c_str()); }

    std::vector<std::string> archives;
    for (auto const& archive : unit_.getArchives()) { archives.push_back("/wholearchive:" + archive); }
    for (auto const& archive : archives) { args.push_back(archive.c_str()); }

    std::string const in = obj.string();
    args.push_back(in.c_str());

    lld::DriverDef linker;

    switch (unit_.getTarget().triple().getOS())
    {
        case llvm::Triple::OSType::Win32:
        {
            linker.f = lld::WinLink;
            linker.d = lld::coff::link;
            args[0]  = "lld-link";
            break;
        }
        default:
            stream << "ance: build: unsupported target OS" << std::endl;
            return false;
    }

    std::string              output;
    llvm::raw_string_ostream output_stream(output);
    lld::Result              result = lld::lldMain(args, output_stream, output_stream, linker);

    stream << output;// Newline added by lld.

    return result.retCode == 0;
}

bool AnceLinker::getTargetRequirements(std::vector<std::string>& libs,
                                       std::vector<std::string>& lib_paths,
                                       std::ostream&             stream)
{
    std::string const system_sdk_directory = "ANCE_SYSTEM_SDK_DIRECTORY";
    char const*       system_sdk_path      = std::getenv(system_sdk_directory.c_str());

    std::string const system_runtime_directory = "ANCE_SYSTEM_RUNTIME_DIRECTORY";
    char const*       system_runtime_path      = std::getenv(system_runtime_directory.c_str());

    if (unit_.getTarget().getOS() == TargetDescriptor::WINDOWS)
    {
        std::string const arch_suffix = unit_.getTarget().is64Bit() ? "x64" : "x86";

        if (system_sdk_path == nullptr)
        {
            stream << R"(ance: build: no system sdk directory set (e.g. ..\Windows Kits\10\Lib\<version>))"
                   << " (" << system_sdk_directory << ")" << std::endl;

            return false;
        }
        else
        {
            std::string const path = system_sdk_path;
            lib_paths.push_back("/libpath:" + path + "\\um\\" + arch_suffix);
            lib_paths.push_back("/libpath:" + path + "\\ucrt\\" + arch_suffix);
        }

        if (system_runtime_path == nullptr)
        {
            stream << R"(ance: build: no system runtime directory set (e.g. ..VC\Tools\MSVC\<version>))"
                   << " (" << system_runtime_directory << ")" << std::endl;

            return false;
        }
        else
        {
            std::string const path = system_runtime_path;
            lib_paths.push_back("/libpath:" + path + "\\lib\\" + arch_suffix);
        }

        libs.emplace_back("/defaultlib:msvcrt.lib");
    }

    return true;
}
