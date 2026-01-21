#include <filesystem>
#include <iostream>

#include <boost/locale.hpp>

#include "ance/sources/SourceTree.h"

#include "ance/ast/Node.h"
#include "ance/ast/Parser.h"

#include "ance/bbt/Function.h"
#include "ance/bbt/Type.h"

#include "ance/cet/Node.h"
#include "ance/cet/Provider.h"
#include "ance/cet/Runner.h"

#include "ance/build/Compiler.h"

#include "CoreDefinitions.h"

namespace ance
{
    static int program(int const argc, char** argv)
    {
        core::Reporter::print(std::cout, "Copyright (c) 2026 Jean Patrick Mathes");

        if (argc != 2)
        {
            core::Reporter::print(std::cout, "command", "Requires exactly one argument");
            return EXIT_FAILURE;
        }

        boost::locale::generator const gen;
        std::locale const              loc = gen("");
        std::locale::global(loc);

        std::filesystem::path file_path(argv[1]);
        if (file_path.is_relative()) file_path = absolute(file_path);
        if (!exists(file_path))
        {
            core::Reporter::print(std::cout, "input", "File does not exist");
            return EXIT_FAILURE;
        }

        std::ostream& out = std::cout;

        std::filesystem::path const base_path = file_path.parent_path();
        std::filesystem::path const file_name = file_path.filename();

        std::filesystem::path const output_path = base_path / "bld";
        create_directories(output_path);

        std::filesystem::path const debug_path = output_path / "dbg";
        create_directories(debug_path);

        sources::SourceTree source_tree {base_path};
        core::Reporter      reporter;
        core::Context       context {debug_path};

        cet::Runner     runner {source_tree, reporter, context};
        build::Compiler compiler {source_tree, reporter, context};// todo: consider using the runner internally

        defineCoreLanguageFunctions(runner);

        int exit_code = EXIT_FAILURE;

        utility::Optional<utility::Owned<cet::Unit>> unit = runner.runOrderedFile(file_name);

        if (unit.hasValue())
        {
            if (compiler.compile(**unit)) { exit_code = EXIT_SUCCESS; }
        }

        reporter.report(source_tree, out);

        return exit_code;

        // todo: refactor segmenter to have state in state struct instead of all the separate variables

        // todo: improve naming in expander
        // todo: improve naming in segmenter

        // todo: improve naming of flows by passing name in expander, adding it as annotation to file node in EST, remove the flow counter in segmenter

        // todo: add all cmp statements and expressions (see old grammar), if a statement/expression is non-cmp add a TODO in the old grammar file
        // todo: also check in old code whether they returned indirect values or direct values, mimic that now through LRef
        // todo: do it step by step, as e.g. the array things require more changes so that array ops have support on types that the temporary and variable classes can use
        // todo: also reduce duplication between temporary and variable

        // todo: rework SourceFile class to read into single string buffer, then use string views instead of line-by-line reading

        // todo: add first non-cmp code (and declarable functions) and do actual compilation
        // todo: build a very minimal CET that heavily relies and uses intrinsics, should be close to LLVM IR in capability and nodes
        // todo: needs its own value type (defined in CET namespace), do not use the one from BBT or LLVM

        // todo: when adding destructors, do not forget that break/continue can also cause them to be called - scope information has to be carried over to bbt and cet
        // todo: do not forget that temporaries are also scoped and require destructors to be called, also ensure that temporaries are not usable outside their scope e.g. with invalid expansion code

        // todo: add the # and @ operators to the grammar, # takes an identifier and returns an identifier value, and @ resolves an entity and gives a reference to the entity

        // todo: when adding erase, check where it is used in expansion, instead use scoping
        // todo: correctly call copy and move functions for all linearized temporary using nodes in BBT and CET
        // todo: global variables with non-cmp initializers need an ordering determined using topological sort
        // todo: think about making the typeof node an intrinsic, would either require an any type or something else for the argument like overloading

        // todo: maybe parametrized function types could be a thing now
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
