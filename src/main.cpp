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

#include "ance/bbt/Node.h"
#include "ance/bbt/Printer.h"
#include "ance/bbt/Grapher.h"
#include "ance/bbt/Segmenter.h"
#include "ance/bbt/Function.h"
#include "ance/bbt/FlowBuilder.h"

#include "ance/cet/Node.h"
#include "ance/cet/Printer.h"
#include "ance/cet/Grapher.h"
#include "ance/cet/Runner.h"
#include "ance/cet/Provider.h"

#include "ance/build/Compiler.h"
#include "ance/core/Type.h"

namespace ance
{
    static int program(int const argc, char** argv)
    {
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
        build::Compiler compiler {source_tree, reporter, context}; // todo: consider using the runner internally

        utility::List<utility::Shared<core::Entity>> provider; // todo: remove / improve the functions
        bbt::FlowBuilder builder (core::Location::global());

        builder.setActiveBasicBlock(builder.createBasicBlock());
        {
            bbt::Temporary const& value = builder.pushVariableRead(core::Identifier::like("value"));

            bbt::Temporary const& str_value = builder.pushTemporary();
            {
                utility::List<std::reference_wrapper<bbt::Temporary const>> args;
                args.emplace_back(value);
                builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::B2Str::instance(), std::move(args), str_value, core::Location::global()));
            }

            bbt::Temporary const& location = builder.pushConstant(core::Value::makeLocation(core::Location::global()));

            bbt::Temporary const& result = builder.pushTemporary();
            {
                utility::List<std::reference_wrapper<bbt::Temporary const>> args;
                args.emplace_back(str_value);
                args.emplace_back(location);
                builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Log::instance(), std::move(args), result, core::Location::global()));
            }
            (void)result;
        }
        provider.emplace_back(utility::makeShared<bbt::Function>(core::Signature::like("print1b",
                core::Signature::Parameter(core::Identifier::like("value"), core::Type::Bool())),
                core::Type::Unit(), builder.build()));

        builder.setActiveBasicBlock(builder.createBasicBlock());
        {
            bbt::Temporary const& value = builder.pushVariableRead(core::Identifier::like("value"));
            bbt::Temporary const& location = builder.pushVariableRead(core::Identifier::like("location"));

            bbt::Temporary const& str_value = builder.pushTemporary();
            {
                utility::List<std::reference_wrapper<bbt::Temporary const>> args;
                args.emplace_back(value);
                builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::B2Str::instance(), std::move(args), str_value, core::Location::global()));
            }

            bbt::Temporary const& result = builder.pushTemporary();
            {
                utility::List<std::reference_wrapper<bbt::Temporary const>> args;
                args.emplace_back(str_value);
                args.emplace_back(location);
                builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Log::instance(), std::move(args), result, core::Location::global()));
            }
            (void)result;
        }
        provider.emplace_back(utility::makeShared<bbt::Function>(core::Signature::like("print2b",
                core::Signature::Parameter(core::Identifier::like("value"), core::Type::Bool()),
                core::Signature::Parameter(core::Identifier::like("location"), core::Type::Location())),
                core::Type::Unit(), builder.build()));

        builder.setActiveBasicBlock(builder.createBasicBlock());
        {
            bbt::Temporary const& value = builder.pushVariableRead(core::Identifier::like("value"));

            bbt::Temporary const& location = builder.pushConstant(core::Value::makeLocation(core::Location::global()));

            bbt::Temporary const& result = builder.pushTemporary();
            {
                utility::List<std::reference_wrapper<bbt::Temporary const>> args;
                args.emplace_back(value);
                args.emplace_back(location);
                builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Log::instance(), std::move(args), result, core::Location::global()));
            }
            (void)result;
        }
        provider.emplace_back(utility::makeShared<bbt::Function>(core::Signature::like("print1s",
                core::Signature::Parameter(core::Identifier::like("value"), core::Type::String())),
                core::Type::Unit(), builder.build()));

        builder.setActiveBasicBlock(builder.createBasicBlock());
        {
            bbt::Temporary const& value = builder.pushVariableRead(core::Identifier::like("value"));
            bbt::Temporary const& location = builder.pushVariableRead(core::Identifier::like("location"));

            bbt::Temporary const& result = builder.pushTemporary();
            {
                utility::List<std::reference_wrapper<bbt::Temporary const>> args;
                args.emplace_back(value);
                args.emplace_back(location);
                builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Log::instance(), std::move(args), result, core::Location::global()));
            }
            (void)result;
        }
        provider.emplace_back(utility::makeShared<bbt::Function>(core::Signature::like("print2s",
                core::Signature::Parameter(core::Identifier::like("value"), core::Type::String()),
                core::Signature::Parameter(core::Identifier::like("location"), core::Type::Location())),
                core::Type::Unit(), builder.build()));

        builder.setActiveBasicBlock(builder.createBasicBlock());
        {
            bbt::Temporary const& file = builder.pushVariableRead(core::Identifier::like("file"));
            bbt::Temporary const& location = builder.pushVariableRead(core::Identifier::like("location"));

            bbt::Temporary const& result = builder.pushTemporary();
            {
                utility::List<std::reference_wrapper<bbt::Temporary const>> args;
                args.emplace_back(file);
                args.emplace_back(location);
                builder.pushStatement(utility::makeOwned<bbt::Intrinsic>(core::Include::instance(), std::move(args), result, core::Location::global()));
            }
            (void)result;
        }
        provider.emplace_back(utility::makeShared<bbt::Function>(core::Signature::like("include",
                core::Signature::Parameter(core::Identifier::like("file"), core::Type::String()),
                core::Signature::Parameter(core::Identifier::like("location"), core::Type::Location())),
                core::Type::Unit(), builder.build()));

        runner.add(cet::Provider::fromList(std::move(provider)));

        int exit_code = EXIT_FAILURE;

        utility::Optional<utility::Owned<cet::Unit>> unit = runner.runOrderedFile(file_name);

        if (unit.hasValue())
        {
            if (compiler.compile(**unit))
            {
                exit_code = EXIT_SUCCESS;
            }
        }

        reporter.report(source_tree, out);

        return exit_code;

        // todo: fix the current error (only happens sometimes)
        // todo: make sure that unresolvable variables are actually detected and cause compiler errors, e.g. at end or in while loops
        // todo: check that global variable references can be resolved this way, also check circular case which should be detected (no runnable run point)

        // todo: think about function calls - creating a new run point for each function call is wrong, instead run points should have a stack
        // todo: a function call would push to the stack of the current run point, every attempt of execution would go directly to the called fucntion
        // todo: when the stack is popped, the outer run point continues execution
        // todo: but the return value has to be stored in the run point too, and the function call has to check on repeated execution whether there is already a return value

        // todo: refactor runner by pulling stuff out into other files

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
