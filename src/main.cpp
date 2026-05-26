#include <filesystem>
#include <iostream>

#include <boost/locale.hpp>

#include "ance/sources/SourceTree.h"

#include "ance/build/Compiler.h"

#include "ance/Version.h"

namespace ance
{
    struct Arguments
    {
        // Required arguments:

        utility::Optional<std::filesystem::path> input_file;

        // Optional arguments:

        bool print_version = false;
        bool trace_enabled = false;
    };

    static utility::Optional<Arguments> parseArguments(std::ostream& out, int const argc, char** argv)
    {
        Arguments arguments;

        for (int index = 1; index < argc; index++)
        {
            std::string_view const arg(argv[index]);

            if (arg == "--version")
            {
                arguments.print_version = true;
            }
            else if (arg == "--trace")
            {
                arguments.trace_enabled = true;
            }
            else if (arg.starts_with("-"))
            {
                core::Reporter::print(out, "command", "Unknown command line argument: " + std::string(arg));
            }
            else
            {
                if (arguments.input_file.hasValue())
                {
                    core::Reporter::print(out, "command", "Multiple input files provided");
                }
                else
                {
                    arguments.input_file = std::filesystem::path(arg);
                }
            }
        }

        if (!arguments.input_file.hasValue() && !arguments.print_version)
        {
            core::Reporter::print(out, "command", "No input file provided");
            return std::nullopt;
        }

        return arguments;
    }

    static int program(int const argc, char** argv)
    {
        boost::locale::generator const gen;
        std::locale const              loc = gen("");
        std::locale::global(loc);

        std::ostream& program_out = std::cout;
        std::ostream& compiler_out = std::cerr;

        utility::Optional<Arguments> const arguments = parseArguments(compiler_out, argc, argv);

        if (!arguments.hasValue()) return EXIT_FAILURE;

        if (arguments->print_version)
        {
            program_out << "ance compiler version " << VERSION << std::endl;
            program_out << "Copyright (c) 2026 Jean Patrick Mathes" << std::endl;
            program_out << std::endl;
        }

        if (!arguments->input_file.hasValue()) return EXIT_SUCCESS;

        std::filesystem::path file_path = arguments->input_file.value();
        if (!exists(file_path))
        {
            core::Reporter::print(compiler_out, "input", "File does not exist");
            return EXIT_FAILURE;
        }

        std::filesystem::path const base_path = file_path.parent_path();
        std::filesystem::path const file_name = file_path.filename();

        std::filesystem::path const output_path = base_path / "bld";
        create_directories(output_path);

        std::filesystem::path const debug_path = output_path / "dbg";
        create_directories(debug_path);

        sources::SourceTree source_tree {base_path};
        core::Reporter      reporter {source_tree, compiler_out, arguments->trace_enabled};
        core::Context       context {debug_path};

        build::Compiler compiler {source_tree, reporter, context};

        int exit_code = EXIT_FAILURE;

        if (compiler.compile(file_name))
            exit_code = EXIT_SUCCESS;

        reporter.report();

        return exit_code;

        // todo: subscript operator, should work on arrays
        // todo: write some related documentation for this, repeat this note for the next step

        // todo: no vector types, instead array types support all operators of their element type and perform them element-wise
        // todo: no vectors yet because that has HW and alignment implications, should not be first class language element
        // todo: write some related documentation for this, repeat this note for the next step

        // todo: look into the calendar note again, streamline, remove changed things, keep up to date

        // todo: rethink intrinsic as an enum, maybe go back to inheritance but also do not use visitor but something else?
        // todo: write some related documentation for this, repeat this note for the next step

        // todo: think about how functions and members and methods make sense for the language
        // todo: maybe also think about doing some form of generics earlier, e.g. without using {}, instead something like foo(x: Type)(y: x) which could be done with syntactic sugar only already
        // todo: but these generics would have the issue of creating a new type every time ??, so either all type creation things need to not do that, or there needs to be a keyword that says that a function is cached (maybe pure, with some constraints?, or maybe all functions should be pure if not said otherwise)
        // todo: finally, think about doing compilation in very basic form first, so we can merge again and go back to the tests

        // todo: integer type, integer literals (need type expressions for them, e.g. Integer(32), UnsignedInteger(64), etc.)
        // todo: ops for all integer types
        // todo: for intrinsics for integers, use a single intrinsic for the operations, e.g. "int_add" and change how intrinsics do type checks
        // todo: pretend that the intrinsics are generic and take generic parameters, e.g. intrinsic "int_add" {N} (a, b)
        // todo: to do this, add a GenericIntrinsicSignature class which is used by IntrinsicSignature, getIntrinsicSignature would take the generic parameters
        // todo: the int types can then simply use string manipulation to put the right N there
        // todo: do not forget to write more documentation comments on this matter

        // todo: bitwise binary ops and shifts
        // todo: write some related documentation for this, repeat this note for the next step

        // todo: reduce duplication between temporary and variable

        // todo: go through all TODOs in the other code, check if completable now or soon or maybe already completed, potentially move them here

        // todo: check grammar for ambiguity and context sensitivity, repeat this step later

        // todo: rework SourceFile class to read into single string buffer, then use string views instead of line-by-line reading

        // todo: struct types
        // todo: think of a nice syntax to create structs and classes, no T{} because that would already have other meanings, and also not T()

        // todo: better reporting: all reports should have an ID (decide whether number or string [!] ), and if possible parameters (maybe they can be extracted from the message builder stream interface, skipping char* and potentially string)
        // todo: reporter then can suppress identical reports, if already reported, using only ID, location and params for check - hash that
        // todo: trace should never be suppressed if identical
        // todo: later, when going back to the tests, they should also assert specific IDs

        // todo: all variants of char and string types and literals, check that char might need to be called codepoint

        // todo: when adding destructors, do not forget that break/continue can also cause them to be called - scope information has to be carried over to bbt and cet
        // todo: do not forget that temporaries are also scoped and require destructors to be called, also ensure that temporaries are not usable outside their scope e.g. with invalid expansion code
        // todo:    for temporaries, they need to be statement scoped, as such the segmenter must add a scope enter and scope exit on every statement (add a is_statement_scope = true for diagnostics)
        // todo: do not forget destructors of global variables - should have reversed order of creation
        // todo: add assertion that when variable or temporary is destroyed in C++, the isDestructed flag is set to true to catch missing destructor calls
        // todo: write some good documentation on this

        // todo: add first runtime code and do actual compilation, maybe have a Lowerer visitor that works in tandem with the runner
        // todo: build a very minimal CET that heavily relies and uses intrinsics, should be close to LLVM IR in capability and nodes
        // todo: might need its own value type (defined in CET namespace), do not use the one from BBT or LLVM
        // todo: the lowering visitor should be eager to evaluation, which means that if compile time evaluation is possible, it will be done
        //       (maybe three visitors would be used: Typer, EagerEvaluator, Lowerer)
        // todo: for this, the CET value type stores whether it is available at compile time (isConstant(), Constant class) and if yes, lowerer delegates to the runner
        // todo: some handling of runner state would be needed so runner would need to be initialized and kept up to date by lowerer when entering functions and maybe scopes and such
        // todo: in a similar fashion, when the runner encounters something that is needed to be runtime, it gives control back to the lowerer, so decide which one is the better entry point
        // todo: this model makes resolving easy - resolving of identifiers always possible at compile time so eager evaluation makes special handling unnecessary
        // todo: this is the point where the tests should be brought back in, maybe deactivate those that certainly won't work yet and maybe prioritize them, add TODOs to bring them back, also improve the documentation and explanation in each working test
        // todo: also add loads of tests for all the new things, e.g. lambdas, better cmp, different types, etc. (see readme as well)
        // todo: do runtime library calls through an intrinsic, e.g. runtime_library_call, the intrinsic would check whether lib is available, would take string (from list of constants), the intrinsic itself would be a compiletime intrinsic that returns a runtime function
        // todo: if a good amount of tests is working, plan to merge into main, put all remaining TODOs into the normal planning, adapt calendar note to be used again
        // todo: write some good documentation on these decisions and ideas

        // todo: time to go back to tests, run them and such (add a mechanism to ignore tests through a file, maybe remove that later again)
        // todo: add more texts to tests, make them a bit more specification-like
        // todo: also write some documentation for each test, and some documentation to the test system in general

        // todo: begin with static typesafety, for now for runtime only, typechecking is done during lowering
        // todo: add utilities to do unification, so inference and stuff like that might also work
        // todo: thanks to eager evaluation, this should actually work easily
        // todo: write some good documentation on these decisions and ideas

        // todo: fully support the compiletime and runtime keywords
        // todo: some statements are only allowed in functions marked as compiletime and some only in runtime
        // todo: think about do-blocks, maybe they should also be markable, or maybe only one of them makes sense for them
        // todo: do not forget to also print those markers in later states, currently they are AST only
        // todo: THINK MORE ABOUT THIS: non-marked can be called from all, runtime only from runtime, compiletime only from compiletime and runtime
        // todo: write some good documentation on these decisions and ideas

        // todo: all the pointer and allocation stuff would only work with runtime code for now

        // todo: pointer type, pointer type expression, uiptr, ptr and diff type (renamed to Diff, Pointer, UIntPointer)
        // todo: also adapt Size type to work like Diff and UIntPointer meaning that it is correctly sized depending on platform

        // todo: casting with as

        // todo: allocation and delete expressions
        // todo: addressof and pointer operations

        // todo: add sizeof (type, expression)

        // todo: add the # operator to the grammar, # takes an identifier and returns an identifier value

        // todo: check what happens when an expression that does not make sense as a statement is used as a statement, e.g. unary op, think about what to do

        // todo: correctly call copy and move functions for all linearized temporary using nodes in BBT and CET
        // todo: global variables with runtime initializers need an ordering determined using topological sort
        // todo: think about making the typeof node an intrinsic, would either require an any type or something else for the argument like overloading

        // todo: maybe parametrized function types could be a thing now, could also need generics or at least varargs

        // todo: when adding serialization of trees for cmp libraries, also serialize the trees of the core language functions and of the types
        // todo: this means on first run the compiler has to build the core language functions and types, serialize them, and later it just loads them (add a command line flag to force rebuild)

        // todo: the compiler should also serialize each file it compiles on EST or BBT level, so that recompilation can be avoided if the file did not change
        // todo: determine which tree is the best for this, so that no other factors like compiler parameters need to be considered
        // todo: at least BBT and CET level should support serialization

        // todo: the compile time code needs a print function that actually prints to std::cout

        // todo: think more about static type checking
        // todo: one idea - use the lowered CET for compile time evaluation as well, there would then actually be two modes of compiletime evaluation
        // todo: 1. static compiletime evaluation (SCE): runs on CET, all types and such are already evaluated and static typing is easy, very machine like
        // todo: 2. dynamic compiletime evaluation (DCE): essentially the current model, uses dynamic typing, not statically type safe
        // todo: the big question is then when to use what mode
        // todo: one idea: unmarked functions use SCE, compiletime functions use SCE except when annotated with dynamic
        // todo: alternative would be for now to always require the model used for compiletime (so either static compiletime or dynamic compiletime)
        // todo: then analyze what is actually useful and common, dynamic compiletime could also be called generator
        // todo: write some good documentation on these decisions and ideas

        // todo: some functionality would be DCE only, such as conditional fields, resolve, ...

        // todo: non-marked code (so neither runtime nor compiletime) should be able to handle pointers and such thanks to SCE as well

        // todo: rethink typeof if it is still an issue, it might be something that is not allowed in DCE mode, should be disallowed with error
        // todo: current usage of typeof in expansion (if expression, match expression) should be replaced with variable inference, in DCE it simply creates an un-allocated, untyped variable so handling that is easy

        // todo: most of the old constructors in ance would become functions / static functions

        // todo: with references, add very basic safety checks in the case of erase of variable which has references to it, e.g. counting them, or so
    }
}

#ifdef ANCE_RELEASE_BUILD
#define ANCE_HANDLE_ERRORS
#endif

int main(int const argc, char** argv)
{
#if defined(ANCE_HANDLE_ERRORS)
    try
    {
        return ance::program(argc, argv);
    }
    catch (std::exception const& e)
    {
        ance::core::Reporter::printCritical(std::cerr, e.what());
        return EXIT_FAILURE;
    }
#else
    return ance::program(argc, argv);
#endif
}
