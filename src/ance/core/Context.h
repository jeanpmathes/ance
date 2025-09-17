#ifndef ANCE_CORE_CONTEXT_H
#define ANCE_CORE_CONTEXT_H

#include <filesystem>
#include <fstream>

namespace ance::core
{
    /// Compilation context for passing meta-information about the current compilation.
    class Context
    {
      public:
        explicit Context(std::filesystem::path const& debug_path);
        ~Context();

        template<class Printer, class Tree>
        void print(Tree const& tree, std::string const& tree_name)
        {
            std::filesystem::path const tree_path = debug_path_ / (tree_name + ".txt");
            std::ofstream               out {tree_path};

            Printer printer {out};
            printer.print(tree);
        }

        template<class Grapher, class Tree>
        void graph(Tree const& tree, std::string const& tree_name)
        {
            std::filesystem::path const tree_path = debug_path_ / (tree_name + ".gml");
            std::ofstream               out {tree_path};

            Grapher grapher {out};
            grapher.graph(tree);
        }

    private:
        std::filesystem::path debug_path_;
    };
}

#endif

