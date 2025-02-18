#include <filesystem>
#include <iostream>

#include <boost/locale.hpp>

#include "ance/sources/SourceTree.h"

#include "ance/ast/Node.h"
#include "ance/ast/Parser.h"

#include "ance/est/Expander.h"
#include "ance/est/Node.h"

#include "ance/ret/Node.h"
#include "ance/ret/Resolver.h"

#include "ance/analyze/Analyzer.h"

#include "ance/bbt/Node.h"
#include "ance/bbt/Segmenter.h"

namespace ance
{
    static int program(const int argc, char** argv)
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

        bool const warnings_as_errors = false; // todo: allow setting

        sources::SourceTree source_tree {base_path};
        core::Reporter      reporter;

        auto check_for_fail = [&source_tree, &reporter, &out]()
        {
            if (reporter.errorCount() > 0 || (warnings_as_errors && reporter.warningCount() > 0))
            {
                reporter.emit(source_tree, out);

                out << "ance: Failed";

                if (reporter.errorCount() == 0)
                    out << " (by warning)";

                return true;
            }

            return false;
        };

        ast::Parser   parser {source_tree, reporter};
        est::Expander expander;
        ret::Resolver resolver;
        analyze::Analyzer analyzer;
        bbt::Segmenter segmenter;

        sources::SourceFile const& primary_file = source_tree.addFile(file_name);
        if (check_for_fail()) return EXIT_FAILURE;

        utility::Owned<ast::Statement> parsed = parser.parse(primary_file.index());
        if (check_for_fail()) return EXIT_FAILURE;

        utility::Owned<est::Statement> expanded = expander.expand(*parsed);
        if (check_for_fail()) return EXIT_FAILURE;

        utility::Owned<ret::Statement> resolved = resolver.resolve(*expanded);
        if (check_for_fail()) return EXIT_FAILURE;

        analyzer.analyze(*resolved);
        if (check_for_fail()) return EXIT_FAILURE;

        utility::Owned<bbt::BasicBlock> segmented = segmenter.segment(*resolved);
        if (check_for_fail()) return EXIT_FAILURE;

        // todo: intermediate steps followed by check for fail

        if (check_for_fail()) return EXIT_FAILURE;

        // todo: create the runner and parser and the intermediate steps
        // todo: parse the file
        // todo: do the intermediate steps
        // todo: give it to the runner

        reporter.emit(source_tree, out);

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
