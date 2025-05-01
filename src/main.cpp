#include <filesystem>
#include <fstream>
#include <iostream>

#include <boost/locale.hpp>

#include "ance/core/Intrinsic.h"

#include "ance/sources/SourceTree.h"

#include "ance/ast/Node.h"
#include "ance/ast/Parser.h"
#include "ance/ast/Printer.h"

#include "ance/est/Expander.h"
#include "ance/est/Node.h"
#include "ance/est/Printer.h"

#include "ance/ret/Node.h"
#include "ance/ret/Printer.h"
#include "ance/ret/Resolver.h"

#include "ance/analyze/Analyzer.h"

#include "ance/bbt/Node.h"
#include "ance/bbt/Printer.h"
#include "ance/bbt/Grapher.h"
#include "ance/bbt/Segmenter.h"

#include "ance/cet/Node.h"
#include "ance/cet/Printer.h"
#include "ance/cet/Grapher.h"
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

    template<class Grapher, class Tree>
    void graph(Tree const& tree, std::filesystem::path const& debug_path, std::string const& tree_name)
    {
        std::filesystem::path const tree_path = debug_path / (tree_name + ".gml");
        std::ofstream               out {tree_path};

        Grapher grapher {out};
        grapher.graph(tree);
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
            reporter.emit(source_tree, out);

            if (reporter.errorCount() > 0 || (warnings_as_errors && reporter.warningCount() > 0))
            {
                out << "ance: " << reporter.errorCount() << " errors, " << reporter.warningCount() << " warnings" << std::endl;
                out << "ance: Failed";

                if (reporter.errorCount() == 0) out << " (by warning)";

                return true;
            }

            reporter.clear();

            return false;
        };

        ast::Parser       parser {source_tree, reporter};
        est::Expander     expander {reporter};
        ret::Resolver     resolver {reporter};
        analyze::Analyzer analyzer {reporter};
        bbt::Segmenter    segmenter {reporter};
        cet::Runner       runner {reporter};
        build::Compiler   compiler {reporter};

        resolver.add(core::Intrinsic::print());

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

        print<ret::Printer>(*resolved, debug_path, "ret");

        analyzer.analyze(*resolved);
        if (check_for_fail()) return EXIT_FAILURE;

        utility::Owned<bbt::Flow> segmented = segmenter.segment(*resolved);
        if (check_for_fail()) return EXIT_FAILURE;

        print<bbt::Printer>(*segmented, debug_path, "bbt");
        graph<bbt::Grapher>(*segmented, debug_path, "bbt");

        utility::Owned<cet::Unit> unit = runner.run(*segmented);
        if (check_for_fail()) return EXIT_FAILURE;

        print<cet::Printer>(*unit, debug_path, "cet");
        graph<cet::Grapher>(*unit, debug_path, "cet");

        compiler.compile(*unit);
        if (check_for_fail()) return EXIT_FAILURE;

        reporter.emit(source_tree, out);

        // todo: in ret the call should not always be replaced with an intrinsic - add call nodes to the later stages, also remove the add method from resolver, instead add addFunction and addIntrinsicAsFunction (takes signature) and the resolver then decides whether to place an intrinsic or call node - print should become function, no intrinsics for now
        // todo: add intrinsics and function calls with arguments - print var for now, no overloading
        // todo: add all expressions (both value and control flow) except runtime-only ones to grammar and support them in the compiler - needs types - do simpler types without the definition bridge, type expressions
        // todo: rethink resolution - it should be done using intrinsics by the runner
        //      todo: rename the RET to SET (scoped element tree) and the resolver to Scoper
        //      todo: change the bbt to allow arbitrary stopping and continuation of execution (linearize by pulling out expression, do not use visitor to run)
        //      todo: when encountering a resolution intrinsic which cannot be resolved yet, stop current execution and return as soon as resolution is possible
        //      todo: for blockers, scopes (internal class of runner and ance type) should memorize everything resolved from the outside, if that is declared inside it causes the blocker error
        //      todo: remove the scope and variable classes from core
        //      todo: for expanding with temporaries, use three new nodes in EST: DeclareTemporary, ReadTemporary, WriteTemporary (the last two have a reference to the declaration) - remove the ugly code to create identifier from location
        // todo: add intrinsic functions to include another file, running the cmp code in there too
        // todo: add intrinsic functions to log (print to console with the ance: info: prefix with new color and source from where it was called), remove the current print functions, think for what adding functions to scoper is still needed (but still keep it probably)
        // todo: add first non-cmp code (and declarable functions) and do actual compilation
        // todo: add unordered scopes, have them as default at file top-level - maybe make distinction explicit in compiler code
        // todo: when adding destructors, do not forget that break/continue can also cause them to be called

        out << "ance: " << reporter.warningCount() << " warnings" << std::endl;
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
