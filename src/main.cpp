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
        core::Reporter      reporter {source_tree, out};
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

        reporter.report();

        return exit_code;

        // todo: adapt lambda syntax so that return type is optional, if omitted it is Unit

        // todo: make sure that flows passed to function ctors are also printed and graphed
        // todo: in printer, put those flows into list that is printed when all other flows are printed
        // todo: in grapher, do the same, needs that all statements are visited

        // todo: check if unreachable code detection works or needs to be added (with return in lambda)

        // todo: remove entity from grammar, put IDENTIFIER directly in access, assignment should require expression on left side (so only one resolve in Expander)

        // todo: add function declarations (for now cmp only, must be in syntax)

        // todo: modernize the cmake, e.g. target variants of commands if that is better

        // todo: add a way to call intrinsics from source code with the intrinsic expression intrinsic "name" (args...)
        // todo: but also add a core function intrinsic("name", args...) that does the same thing but is a normal function call

        // todo: spend some time improving Optional, Shared and Owned

        // todo: define the core language functions using code instead of hardcoding the trees - code would be a string in C++ file, would need an entire chain to parse and transform into flows
        // todo: this requires that the type context is shared between all runers, so create a global type context instead of one per runner
        // todo: the intrinsic function can currently probably not be created in source code because of the varargs, so add a TODO there, or maybe add some more stuff
        // todo: probably delete the flow builder

        // todo: add all cmp statements and expressions (see old grammar), if a statement/expression is non-cmp add a TODO in the old grammar file
        // todo: also check in old code whether they returned indirect values or direct values, mimic that now through LRef
        // todo: do it step by step, as e.g. the array things require more changes so that array ops have support on types that the temporary and variable classes can use
        // todo: WHEN WORKING ON TYPES: TYPES SHOULD DEFINE THEIR OPS USING SOURCE CODE (HARDCODED IN C++), just like the core functions, using intrinsics

        // todo: reduce duplication between temporary and variable

        // todo: rework SourceFile class to read into single string buffer, then use string views instead of line-by-line reading

        // todo: add first non-cmp code and do actual compilation, maybe have a Lowerer visitor that works in tandem with the runner
        // todo: build a very minimal CET that heavily relies and uses intrinsics, should be close to LLVM IR in capability and nodes
        // todo: might need its own value type (defined in CET namespace), do not use the one from BBT or LLVM
        // todo: this is the point where the tests should be brought back in, maybe deactivate those that certainly won't work yet and maybe prioritize them, add TODOs to bring them back
        // todo: also add loads of tests for all the new things, e.g. lambdas, better cmp, different types, etc.

        // todo: when adding destructors, do not forget that break/continue can also cause them to be called - scope information has to be carried over to bbt and cet
        // todo: do not forget that temporaries are also scoped and require destructors to be called, also ensure that temporaries are not usable outside their scope e.g. with invalid expansion code

        // todo: add the # and @ operators to the grammar, # takes an identifier and returns an identifier value, and @ resolves an entity and gives a reference to the entity

        // todo: when adding erase, check where it is used in expansion, instead use scoping
        // todo: correctly call copy and move functions for all linearized temporary using nodes in BBT and CET
        // todo: global variables with non-cmp initializers need an ordering determined using topological sort
        // todo: think about making the typeof node an intrinsic, would either require an any type or something else for the argument like overloading

        // todo: maybe parametrized function types could be a thing now, could also need generics or at least varargs

        // todo: when adding serialization of trees for cmp libraries, also serialize the trees of the core language functions and of the types
        // todo: this means on first run the compiler has to build the core language functions and types, serialize them, and later it just loads them (add a command line flag to force rebuild)

        // todo: the compiler should also serialize each file it compiles on EST or BBT level, so that recompilation can be avoided if the file did not change
        // todo: determine which tree is the best for this, so that no other factors like compiler paramters need to be considered
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
