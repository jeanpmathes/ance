#include <filesystem>
#include <fstream>
#include <iostream>

#include <boost/locale.hpp>

#include "ance/core/Function.h"
#include "ance/core/Intrinsic.h"

#include "ance/sources/SourceTree.h"

#include "ance/ast/Node.h"
#include "ance/ast/Parser.h"
#include "ance/ast/Printer.h"

#include "ance/est/Expander.h"
#include "ance/est/Node.h"
#include "ance/est/Printer.h"

#include "ance/bbt/Node.h"
#include "ance/bbt/Printer.h"
#include "ance/bbt/Grapher.h"
#include "ance/bbt/Segmenter.h"

#include "ance/cet/Node.h"
#include "ance/cet/Printer.h"
#include "ance/cet/Grapher.h"
#include "ance/cet/Runner.h"

#include "ance/build/Compiler.h"
#include "ance/core/Type.h"

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
        bbt::Segmenter    segmenter {reporter};
        cet::Runner       runner {reporter};
        build::Compiler   compiler {reporter};

        core::Function const print_fn(core::Signature::like("print"), core::Type::Unit(), [](auto&) { std::cout << "PRINT[]" << std::endl; });
        segmenter.add(print_fn);// todo: remove
        core::Function const print_var_fn(core::Signature::like("print_bool", core::Type::Bool()), core::Type::Unit(), [](auto& args) {
            std::cout << "PRINT[" << args[0]->toString() << "]" << std::endl;
        });
        segmenter.add(print_var_fn);// todo: remove

        sources::SourceFile const& primary_file = source_tree.addFile(file_name);
        if (check_for_fail()) return EXIT_FAILURE;

        utility::Owned<ast::Statement> parsed = parser.parse(primary_file.index());
        if (check_for_fail()) return EXIT_FAILURE;

        print<ast::Printer>(*parsed, debug_path, "ast");

        utility::Owned<est::Statement> expanded = expander.expand(*parsed);
        if (check_for_fail()) return EXIT_FAILURE;

        print<est::Printer>(*expanded, debug_path, "est");

        utility::Owned<bbt::Flow> segmented = segmenter.segment(*expanded);
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

        // todo: do the TODO in Runner::Scope::find

        // todo: add intrinsic functions to log (print to console with the ance: info: prefix with new color and source from where it was called), remove the current print functions, think for what adding functions to scoper is still needed (but still keep it probably)

        // todo: add unordered scopes, have them as default at file top-level except for the primary file - maybe make distinction explicit in compiler code
        // todo: add intrinsic functions to include another file, running the cmp code in there too

        // todo: add global variables so that circular dependencies can exist

        // todo: change the runner to allow arbitrary stopping and continuation of execution
        // todo: it should have a list of run-points and if running one of those stops it continues with the next one
        // todo: when encountering a resolution intrinsic which cannot be resolved yet, stop current execution and return as soon as resolution is possible

        // todo: remove essentially everything from the CET as it has to be rebuilt anyways
        // todo: rethink core classes like Variable, Value, Function, Type, ... and maybe remove them, going for per-tree classes instead or even usage of nodes (maybe use limited variants in the earlier steps, e.g. type enums for the ast, make current type and value and entity a thing of the bbt)

        // todo: instead of passing an allocate lambda to the intrinsics, the entity ref should have a read and write function with validation whether it is allowed, each variable thus stores the value instead of one large variable array
        // todo: and the variables / entities would be stored in the scope they are delcared in

        // todo: add most expressions (both value and control flow) except runtime-only ones to grammar and support them in the compiler

        // todo: add first non-cmp code (and declarable functions) and do actual compilation

        // todo: when adding destructors, do not forget that break/continue can also cause them to be called - scope information has to be carried over to bbt and cet
        // todo: do not forget that temporaries are also scoped and require destructors to be called, also ensure that temporaries are not usable outside their scope e.g. with invalid expansion code

        // todo: add the # and @ operators to the grammar, # takes an identifier and returns an identifier value, and @ resolves an entity and gives a reference to the entity

        // todo: when adding erase, check where it is used in expansion, instead use scoping
        // todo: correctly call copy and move functions for all linearized temporary using nodes in BBT and CET
        // todo: global variables with non-cmp initializers need an ordering determined using topological sort
        // todo: think about making the typeof node an intrinsic, would either require an any type or something else for the argument like overloading
        // todo: the entity_ref type should instead become an entity type and the intrinsic simply returns a reference to that
        // todo: when inheritance becomes a thing then entity should have subclasses like variable and function -> add that to the inheritance note in planning

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
