#include <filesystem>
#include <iostream>

#include <llvm/Support/Host.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>

#include <boost/locale.hpp>

#include "compiler/AnceCompiler.h"
#include "compiler/AnceLinker.h"
#include "compiler/Application.h"
#include "compiler/Packages.h"
#include "compiler/Project.h"
#include "compiler/ProjectDescription.h"
#include "compiler/SourceTree.h"
#include "lang/ApplicationVisitor.h"
#include "validation/ValidationLogger.h"

static Optional<int> emit(SourceTree&        tree,
                          ValidationLogger&  validation_logger,
                          std::ostream&      out,
                          std::string const& step_name)
{
    validation_logger.emitMessages(tree.getSourceFiles(), out, step_name);

    if (validation_logger.errorCount() != 0
        || (tree.unit().isWarningsAsErrors() && validation_logger.warningCount() != 0))
    {
        bool const failed_by_warning = validation_logger.errorCount() == 0;

        out << "ance: validation: Failed";
        if (failed_by_warning) out << " (by warning)";
        out << std::endl;

        return EXIT_FAILURE;
    }

    validation_logger.clear();

    return {};
}

/**
 * The first validation step. Operates on the AST. 
 */
static Optional<int> validateTree(SourceTree& tree, ValidationLogger& validation_logger, std::ostream& out)
{
    size_t const fatal_syntax_error_count = tree.emitMessages(out);

    if (fatal_syntax_error_count != 0) return EXIT_FAILURE;

    tree.buildAbstractSyntaxTree();

    tree.unit().preValidate();

    tree.unit().validate(validation_logger);

    return emit(tree, validation_logger, out, "tree");
}

/**
 * The second validation steps. Operates on the CFG.
 */
static Optional<int> validateFlow(SourceTree& tree, ValidationLogger& validation_logger, std::ostream& out)
{
    tree.unit().validateFlow(validation_logger);

    return emit(tree, validation_logger, out, "flow");
}

static std::filesystem::path getResultPath(std::filesystem::path const& bin_dir, Unit& unit, llvm::Triple const& triple)
{
    return bin_dir / (unit.getName() + unit.getType().getExtension(triple));
}

static Optional<int> build(SourceTree&                  tree,
                           llvm::Triple const&          triple,
                           std::filesystem::path const& obj_dir,
                           std::filesystem::path const& bin_dir,
                           std::ostream&                out)
{
    AnceCompiler compiler(tree, triple);
    AnceLinker   linker(tree.unit());

    std::filesystem::create_directories(obj_dir);
    std::filesystem::create_directories(bin_dir);

    std::filesystem::path const ilr = obj_dir / (tree.unit().getName() + ".ll");
    std::filesystem::path const obj = obj_dir / (tree.unit().getName() + ".o");
    std::filesystem::path const res = getResultPath(bin_dir, tree.unit(), tree.unit().getTargetTriple());

    compiler.compile(ilr);
    compiler.emitObject(obj);

    bool const ok = linker.link(obj, res, out);

    if (ok) return {};

    return EXIT_FAILURE;
}

static Optional<int> run(std::ostream&                          out,
                         std::filesystem::path const&           project_file_path,
                         Optional<std::filesystem::path> const& override_build_dir,
                         Packages const&                        packages)
{
    std::filesystem::path build_dir = project_file_path.parent_path() / "bld";
    if (override_build_dir.hasValue()) build_dir = *override_build_dir;

    std::filesystem::path const project_definition_root = build_dir / "def";
    std::filesystem::path const project_definition_bin  = project_definition_root / "bin";
    std::filesystem::path const project_definition_obj  = project_definition_root / "obj";

    llvm::Triple const triple(llvm::sys::getDefaultTargetTriple());

    ProjectDescription::Description description;
    ValidationLogger                validation_logger;

    {
        ProjectDescription project_description(project_file_path);
        project_description.setBinaryDescriptionPath(
            getResultPath(project_definition_bin, project_description, triple));

        out << "======================== Build [ " << project_file_path.stem().string()
            << " ] ========================" << std::endl;

        if (project_description.isRefreshRequired())
        {
            SourceTree tree(project_description);
            tree.parse();

            auto ok = tree.unit().preparePackageDependencies(packages, run, project_definition_root, out);
            if (!ok) return EXIT_FAILURE;

            out << "ance: input: Project file read" << std::endl;

            auto error = validateTree(tree, validation_logger, out);
            if (error.hasValue()) return error.value();

            project_description.preBuild();

            error = validateFlow(tree, validation_logger, out);
            if (error.hasValue()) return error.value();

            error = build(tree, triple, project_definition_obj, project_definition_bin, out);
            if (error.hasValue()) return error.value();
        }

        bool const ok = project_description.loadDescription();
        if (!ok)
        {
            out << "ance: input: Project description invalid" << std::endl;
            return EXIT_FAILURE;
        }

        description = project_description.description();
    }

    {
        Project project(std::move(description));

        Application& application = project.getApplication();
        auto         ok          = application.preparePackageDependencies(packages, run, build_dir, out);
        if (!ok) return EXIT_FAILURE;

        SourceTree   tree(application);
        size_t const count = tree.parse();

        out << "ance: input: " << count << " source file(s) read" << std::endl;

        auto error = validateTree(tree, validation_logger, out);
        if (error.hasValue()) return error.value();

        std::filesystem::path const obj_dir = build_dir / triple.getTriple() / "obj";
        std::filesystem::path const bin_dir = build_dir / triple.getTriple() / "bin";

        if (application.isEmittingExtras()) application.emitAsSource(obj_dir / "input.nc");

        application.preBuild();

        if (application.isEmittingExtras()) application.emitAsSource(obj_dir / "input_prebuild.nc");

        error = validateFlow(tree, validation_logger, out);
        if (error.hasValue()) return error.value();

        error = build(tree, triple, obj_dir, bin_dir, out);
        if (error.hasValue()) return error.value();

        out << "ance: build: Success" << std::endl;
    }

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

    char const* package_directory = std::getenv("ANCE_PACKAGE_DIRECTORY");
    if (package_directory == nullptr)
    {
        std::cout << "ance: packages: ANCE_PACKAGE_DIRECTORY is not set" << std::endl;
        return EXIT_FAILURE;
    }

    Packages const packages(package_directory);

    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmParsers();
    llvm::InitializeAllAsmPrinters();

    std::filesystem::path project_file_path(argv[1]);
    if (project_file_path.is_relative()) project_file_path = std::filesystem::absolute(project_file_path);
    if (!std::filesystem::exists(project_file_path))
    {
        std::cout << "ance: input: Project file does not exist." << std::endl;
        return EXIT_FAILURE;
    }

    auto result = run(std::cout, project_file_path, std::nullopt, packages);

    llvm::llvm_shutdown();

    return result.valueOr(EXIT_SUCCESS);
}
