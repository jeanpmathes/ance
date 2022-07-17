#include "AnceLinker.h"

#include <lld/Common/Driver.h>

AnceLinker::AnceLinker(std::optional<std::reference_wrapper<const data::Element>> link_config)
{
    if (link_config)
    {
        const auto& link_config_root = link_config->get();

        auto libpath_list = link_config_root["libpath"];

        if (libpath_list)
        {
            for (auto libpath : libpath_list->get())
            {
                auto libpath_str = libpath.get().asString();
                if (!libpath_str) continue;

                std::filesystem::path path(libpath_str->get());
                lib_paths_.push_back("/libpath:" + path.string());
            }
        }

        auto lib_list = link_config_root["lib"];

        if (lib_list)
        {
            for (auto lib : lib_list->get())
            {
                auto lib_str = lib.get().asString();
                if (!lib_str) continue;

                libs_.push_back("/defaultlib:" + lib_str->get());
            }
        }
    }
}

bool AnceLinker::link(const std::filesystem::path& obj, const std::filesystem::path& exe)
{
    std::vector<const char*> args;
    args.push_back("lld");

    args.push_back("/verbose");

    args.push_back("/debug:FULL");

    args.push_back("/machine:x64");
    args.push_back("/subsystem:console");

    args.push_back("/entry:_start");

    std::string out = "/out:" + exe.string();
    args.push_back(out.c_str());

    for (const auto& libpath : lib_paths_) { args.push_back(libpath.c_str()); }

    for (const auto& lib : libs_) { args.push_back(lib.c_str()); }

    std::string in = obj.string();
    args.push_back(in.c_str());

    return lld::mingw::link(args, llvm::outs(), llvm::errs(), false, false);
}
