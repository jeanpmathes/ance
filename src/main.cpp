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

        // todo: WHEN WORKING ON TYPES: TYPES SHOULD DEFINE THEIR OPS USING SOURCE CODE (HARDCODED IN C++), just like the core functions, using intrinsics

        // todo: unary ops (for floats and maybe others)
        // todo: relational and equality ops (for string, size, bool, floats and maybe others)

        // todo: parenthesis expression

        // todo: function overloading / function groups

        // todo: constructors as callable types

        // todo: integer type, integer literals (need type expressions for them, e.g. Int{32}, UInt{64}, etc.)
        // todo: ops for all integer types
        // todo: for intrinsics for integers, use a single intrinsic for the operations, e.g. "int_add" and change how intrinsics do type checks
        // todo: pretend that the intrinsics are generic and take generic parameters, e.g. intrinsic "int_add" {N} (a, b)
        // todo: to do this, add a GenericIntrinsicSignature class which is used by IntrinsicSignature, getIntrinsicSignature would take the generic parameters
        // todo: the int types can then simply use string manipulation to put the right N there

        // todo: bitwise binary ops and shifts

        // todo: array type, array literals
        // todo: subscript operator

        // todo: vector type, vector literals

        // todo: reduce duplication between temporary and variable

        // todo: go through all TODOs in the other code, check if completable now or soon or maybe already completed, potentially move them here

        // todo: check grammar for ambiguity, repeat this step later

        // todo: rework SourceFile class to read into single string buffer, then use string views instead of line-by-line reading

        // todo: struct types

        // todo: better reporting: all reports should have an ID (decide whether number or string [!] ), and if possible parameters (maybe they can be extracted from the message builder stream interface, skipping char* and potentially string)
        // todo: reporter then can suppress identical reports, if already reported, using only ID, location and params for check - hash that
        // todo: trace should never be suppressed if identical
        // todo: later, when going back to the tests, they should also assert specific IDs (find

        // todo: all variants of char and string types and literals, check that char might need to be called codepoint

        // todo: when adding destructors, do not forget that break/continue can also cause them to be called - scope information has to be carried over to bbt and cet
        // todo: do not forget that temporaries are also scoped and require destructors to be called, also ensure that temporaries are not usable outside their scope e.g. with invalid expansion code
        // todo:    for temporaries, they need to be statement scoped, as such the segmenter must add a scope enter and scope exit on every statement (add a is_statement_scope = true for diagnostics)
        // todo: do not forget destructors of global variables - should have reversed order of creation
        // todo: add assertion that when variable or temporary is destroyed in C++, the isDestructed flag is set to true to catch missing destructor calls

        // todo: add first runtime code and do actual compilation, maybe have a Lowerer visitor that works in tandem with the runner
        // todo: build a very minimal CET that heavily relies and uses intrinsics, should be close to LLVM IR in capability and nodes
        // todo: might need its own value type (defined in CET namespace), do not use the one from BBT or LLVM
        // todo: this is the point where the tests should be brought back in, maybe deactivate those that certainly won't work yet and maybe prioritize them, add TODOs to bring them back
        // todo: also add loads of tests for all the new things, e.g. lambdas, better cmp, different types, etc.
        // todo: do runtime library calls through an intrinsic, e.g. runtime_library_call, the intrinsic would check whether lib is available, would take string (from list of constants), the intrinsic itself would be a compiletime intrinsic that returns a runtime function

        // todo: time to go back to tests, run them and such (add a mechanism to ignore tests through a file, maybe remove that later again)
        // todo: add more texts to tests, make them a bit more specification-like

        // todo: pointer type, pointer type expression, uiptr, ptr and diff type (renamed to Diff, Pointer, UIntPointer)
        // todo: also adapt Size type to work like Diff and UIntPointer meaning that it is correctly sized depending on platform

        // todo: casting with as

        // todo: allocation and delete expressions
        // todo: addressof and pointer operations

        // todo: fully support the compiletime and runtime keywords
        // todo: some statements are only allowed in functions marked as compiletime and some only in runtime
        // todo: think about do-blocks, maybe they should also be markable, or maybe only one of them makes sense for them
        // todo: do not forget to also print those markers in later states, currently they are AST only
        // todo: THINK MORE ABOUT THIS: non-marked can be called from all, runtime only from runtime, compiletime only from compiletime and runtime

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
        // todo: determine which tree is the best for this, so that no other factors like compiler paramters need to be considered

        // todo: the compile time code needs a print function that actually prints to std::cout

        // todo: when compile time is actually typesafe make the compile time execution more machine-like
        // todo: this would mean that pointer ops and such make sense as actual bytes are stored and manipulated
        // todo: but then values can no longer story their type, static typing is needed and to keep type safety the compile time needs to actually do typing
        // todo: static typing is essential for typeof as well, so that it no longer needs to evaluate the expressions which is important for if expression, match expression
        // todo: when typeof gives the static type, a new expression to get the dynamic type is needed as well

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
