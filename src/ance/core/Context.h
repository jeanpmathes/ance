#ifndef ANCE_CORE_CONTEXT_H
#define ANCE_CORE_CONTEXT_H

#include <filesystem>
#include <fstream>
#include <string>

namespace ance::core
{
    /// Compilation context for passing meta-information about the current compilation.
    class Context
    {
      public:
        explicit Context(std::filesystem::path const& debug_path);
        ~Context();

        template<class Printer, class Tree>
        void print(Tree const& tree, std::string const& tree_name, std::filesystem::path const& file_path)
        {
            std::ofstream out {makeOutputPath(file_path, tree_name, ".txt")};

            Printer printer {out};
            printer.print(tree);
        }

        template<class Grapher, class Tree>
        void graph(Tree const& tree, std::string const& tree_name, std::filesystem::path const& file_path)
        {
            std::ofstream out {makeOutputPath(file_path, tree_name, ".gml")};

            Grapher grapher {out};
            grapher.graph(tree);
        }

      private:
        [[nodiscard]] std::filesystem::path makeOutputPath(std::filesystem::path const& file_path,
                                                           std::string const&           tree_name,
                                                           std::string const&           extension) const
        {
            std::filesystem::path const normalized = file_path.lexically_normal();
            std::filesystem::path const relative   = normalized.is_absolute() ? normalized.relative_path() : normalized;

            std::filesystem::path const stage_directory = debug_path_ / relative;
            std::filesystem::create_directories(stage_directory);

            return stage_directory / (tree_name + extension);
        }

        std::filesystem::path debug_path_;
    };
}

#endif
