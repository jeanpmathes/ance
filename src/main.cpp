#include <filesystem>
#include <iostream>

#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>

#include <boost/locale.hpp>

#include "compiler/AnceCompiler.h"
#include "compiler/AnceLinker.h"
#include "compiler/Application.h"
#include "compiler/Project.h"
#include "compiler/ProjectDescription.h"
#include "compiler/SourceTree.h"
#include "lang/ApplicationVisitor.h"
#include "validation/ValidationLogger.h"

/**
 * The first validation step. Operates on the AST. 
 */
static Optional<int> validateTree(SourceTree& tree, ValidationLogger& validation_logger)
{
    size_t const fatal_syntax_error_count = tree.emitMessages();

    if (fatal_syntax_error_count != 0) return EXIT_FAILURE;

    tree.buildAbstractSyntaxTree();

    tree.unit().preValidate();

    tree.unit().validate(validation_logger);

    if (validation_logger.errorCount() != 0)
    {
        validation_logger.emitMessages(tree.getSourceFiles());
        return EXIT_FAILURE;
    }

    return {};
}

/**
 * The second validation steps. Operates on the CFG.
 */
static Optional<int> validateFlow(SourceTree& tree, ValidationLogger& validation_logger)
{
    tree.unit().validateFlow(validation_logger);

    validation_logger.emitMessages(tree.getSourceFiles());

    if (validation_logger.errorCount() != 0) return EXIT_FAILURE;

    return {};
}

static Optional<int> build(SourceTree& tree, std::filesystem::path const& obj_dir, std::filesystem::path const& bin_dir)
{
    AnceCompiler compiler(tree.unit(), tree);
    AnceLinker   linker(tree.unit());

    std::filesystem::create_directories(obj_dir);
    std::filesystem::create_directories(bin_dir);

    std::filesystem::path const ilr = obj_dir / (tree.unit().getName() + ".ll");
    std::filesystem::path const obj = obj_dir / (tree.unit().getName() + ".o");
    std::filesystem::path const res = bin_dir / (tree.unit().getName() + tree.unit().getType().getExtension());

    compiler.compile(ilr);
    compiler.emitObject(obj);

    bool const ok = linker.link(obj, res);

    if (!ok) return EXIT_FAILURE;

    tree.unit().setResultPath(res);

    return {};
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "ance: command: Requires exactly one parameter." << std::endl;

        return EXIT_FAILURE;
    }

    boost::locale::generator const gen;
    std::locale::global(gen(""));

    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    std::filesystem::path project_file_path(argv[1]);
    if (project_file_path.is_relative()) project_file_path = std::filesystem::absolute(project_file_path);

    std::filesystem::path const bld_dir = project_file_path.parent_path() / "bld";

    ProjectDescription::Description description;
    ValidationLogger                validation_logger;

    {
        ProjectDescription project_description(project_file_path);

        std::cout << "============ Build [ " << project_description.getName() << " ] ============" << std::endl;

        SourceTree tree(project_description);
        tree.parse();

        std::cout << "ance: input: project file read" << std::endl;

        auto error = validateTree(tree, validation_logger);
        if (error.hasValue()) return error.value();

        project_description.preBuild();

        error = validateFlow(tree, validation_logger);
        if (error.hasValue()) return error.value();

        std::filesystem::path const  obj_dir = bld_dir / "prj";
        std::filesystem::path const& bin_dir = bld_dir;

        error = build(tree, obj_dir, bin_dir);
        if (error.hasValue()) return error.value();

        bool const ok = project_description.loadDescription();
        if (!ok)
        {
            std::cout << "ance: input: project description invalid" << std::endl;
            return EXIT_FAILURE;
        }

        description = project_description.description();
    }

    {
        Project project(std::move(description));

        Application& application = project.getApplication();

        SourceTree   tree(application);
        size_t const count = tree.parse();

        std::cout << "ance: input: " << count << " source file(s) read" << std::endl;

        auto error = validateTree(tree, validation_logger);
        if (error.hasValue()) return error.value();

        std::filesystem::path const obj_dir = bld_dir / "obj";
        std::filesystem::path const bin_dir = bld_dir / "bin";

        application.emitAsSource(obj_dir / "input.nc");
        application.preBuild();
        application.emitAsSource(obj_dir / "input_prebuild.nc");

        error = validateFlow(tree, validation_logger);
        if (error.hasValue()) return error.value();

        error = build(tree, obj_dir, bin_dir);
        if (error.hasValue()) return error.value();
    }

    llvm::llvm_shutdown();
}
