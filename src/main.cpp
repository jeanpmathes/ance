#include <filesystem>
#include <fstream>
#include <iostream>

#include <boost/locale.hpp>

#include "ance/sources/SourceTree.h"

#include "ance/ast/Node.h"
#include "ance/ast/Parser.h"
#include "ance/ast/Printer.h"

#include "ance/est/Expander.h"
#include "ance/est/Node.h"
#include "ance/est/Printer.h"

#include "ance/ret/Node.h"
#include "ance/ret/Resolver.h"

#include "ance/analyze/Analyzer.h"

#include "ance/bbt/Node.h"
#include "ance/bbt/Segmenter.h"

#include "ance/cet/Node.h"
#include "ance/cet/Runner.h"

#include "ance/build/Compiler.h"

namespace ance
{
    template<class Printer, class Tree>
    void print(Tree const& tree, std::filesystem::path const& debug_path, std::string const& tree_name)
    {
        std::filesystem::path const tree_path = debug_path / (tree_name + ".txt");
        std::ofstream               out {tree_path};

        Printer printer {out};
        printer.print(tree);
    }

    static int program(int const argc, char** argv)
    {
        if (argc != 2)
        {
            std::cout << "ance: command: Requires exactly one argument" << std::endl;
            return EXIT_FAILURE;
        }

        boost::locale::generator const gen;
        std::locale const              loc = gen("");
        std::locale::global(loc);

        std::filesystem::path file_path(argv[1]);
        if (file_path.is_relative()) file_path = absolute(file_path);
        if (!exists(file_path))
        {
            std::cout << "ance: input: File does not exist" << std::endl;
            return EXIT_FAILURE;
        }

        std::ostream& out = std::cout;

        std::filesystem::path const base_path = file_path.parent_path();
        std::filesystem::path const file_name = file_path.filename();

        std::filesystem::path const output_path = base_path / "bld";
        create_directories(output_path);

        std::filesystem::path const debug_path = output_path / "dbg";
        create_directories(debug_path);

        bool const warnings_as_errors = false;// todo: allow setting

        sources::SourceTree source_tree {base_path};
        core::Reporter      reporter;

        auto check_for_fail = [&source_tree, &reporter, &out]() {
            if (reporter.errorCount() > 0 || (warnings_as_errors && reporter.warningCount() > 0))
            {
                reporter.emit(source_tree, out);

                out << "ance: Failed";

                if (reporter.errorCount() == 0) out << " (by warning)";

                return true;
            }

            return false;
        };

        ast::Parser       parser {source_tree, reporter};
        est::Expander     expander {reporter};
        ret::Resolver     resolver {reporter};
        analyze::Analyzer analyzer {reporter};
        bbt::Segmenter    segmenter {reporter};
        cet::Runner       runner {reporter};
        build::Compiler   compiler {reporter};

        sources::SourceFile const& primary_file = source_tree.addFile(file_name);
        if (check_for_fail()) return EXIT_FAILURE;

        utility::Owned<ast::Statement> parsed = parser.parse(primary_file.index());
        if (check_for_fail()) return EXIT_FAILURE;

        print<ast::Printer>(*parsed, debug_path, "ast");

        utility::Owned<est::Statement> expanded = expander.expand(*parsed);
        if (check_for_fail()) return EXIT_FAILURE;

        print<est::Printer>(*expanded, debug_path, "est");

        utility::Owned<ret::Statement> resolved = resolver.resolve(*expanded);
        if (check_for_fail()) return EXIT_FAILURE;

        analyzer.analyze(*resolved);
        if (check_for_fail()) return EXIT_FAILURE;

        utility::Owned<bbt::BasicBlock> segmented = segmenter.segment(*resolved);
        if (check_for_fail()) return EXIT_FAILURE;

        utility::Owned<cet::Unit> unit = runner.run(*segmented);
        if (check_for_fail()) return EXIT_FAILURE;

        compiler.compile(*unit);
        if (check_for_fail()) return EXIT_FAILURE;

        reporter.emit(source_tree, out);

        // todo: add a printer visitor for each tree: ret, bbt, cet
        // todo: add the intrinsic registration to resolver and an intrinsic class (contain no functionality, instead intrinsic visitor), remove identifier from intrinsic nodes and use intrinsic refs instead
        //      ->> to support writing with hardcoded intrinsics, some intrinsics should have a class with singletons, intrinsics use an intrinsic visitor with the hardcoded types and one dynamic intrinsic for all others 
        // todo: add all control flow statements to grammar and support them in the compiler
        // todo: add all expressions (both value and control flow) to grammar and support them in the compiler - needs types - do simpler types without the definition bridge
        // todo: add intrinsic functions to include another file, running the cmp code in there too
        // todo: add first non-cmp code and do actual compilation

        out << "ance: Success";

        return EXIT_SUCCESS;
    }
}

//#define ANCE_HANDLE_ERRORS

int main(int const argc, char** argv)
{
#if defined(ANCE_HANDLE_ERRORS)
    try
    {
        return ance::program(argc, argv);
    }
    catch (std::exception const& e)
    {
        std::cerr << "ance: internal error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
#else
    return ance::program(argc, argv);
#endif
}
