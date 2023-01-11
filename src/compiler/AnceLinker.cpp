#include "AnceLinker.h"

#include <lld/Common/Driver.h>

#include "compiler/Unit.h"
#include "lang/ApplicationVisitor.h"

AnceLinker::AnceLinker(Unit& unit) : unit_(unit) {}

bool AnceLinker::link(std::filesystem::path const& obj, std::filesystem::path const& app)
{
    std::vector<char const*> args;
    args.push_back("lld");

    args.push_back("/debug:FULL");

    args.push_back("/machine:x64");
    args.push_back("/subsystem:console");

    unit_.getType().addLinkerArguments(args);

    std::string const out = "/out:" + app.string();
    args.push_back(out.c_str());

    std::vector<std::string> lib_paths;
    for (auto const& libpath : unit_.getLibraryPaths()) { lib_paths.push_back("/libpath:" + libpath); }
    for (auto const& libpath : lib_paths) { args.push_back(libpath.c_str()); }

    std::vector<std::string> libs;
    for (auto const& lib : unit_.getLibraries()) { libs.push_back("/defaultlib:" + lib); }
    for (auto const& lib : libs) { args.push_back(lib.c_str()); }

    std::string const in = obj.string();
    args.push_back(in.c_str());

    return lld::mingw::link(args, llvm::outs(), llvm::errs(), false, false);
}
