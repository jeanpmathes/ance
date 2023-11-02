#include <filesystem>
#include <iostream>

#include <llvm/Support/Host.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>

#include <boost/locale.hpp>
#include <utility>

#include "compiler/AnceCompiler.h"
#include "compiler/AnceLinker.h"
#include "compiler/Application.h"
#include "compiler/Packages.h"
#include "compiler/Project.h"
#include "compiler/ProjectDescription.h"
#include "compiler/SourceTree.h"
#include "lang/ApplicationVisitor.h"
#include "validation/ValidationLogger.h"

static bool emit(SourceTree& tree, ValidationLogger& validation_logger, std::ostream& out, std::string const& step_name)
{
    validation_logger.emitMessages(tree.getSourceFiles(), out, step_name);

    if (validation_logger.errorCount() != 0
        || (tree.unit().isWarningsAsErrors() && validation_logger.warningCount() != 0))
    {
        bool const failed_by_warning = validation_logger.errorCount() == 0;

        out << std::endl;
        out << "ance: validation: Failed";
        if (failed_by_warning) out << " (by warning)";
        out << std::endl;

        return false;
    }

    validation_logger.clear();

    return true;
}

/**
 * The first validation step. Operates on the AST. 
 */
static bool validateTree(SourceTree& tree, ValidationLogger& validation_logger, std::ostream& out)
{
    size_t const fatal_syntax_error_count = tree.emitMessages(out);

    if (fatal_syntax_error_count != 0) return false;

    tree.buildAbstractSyntaxTree();

    tree.unit().preValidate();

    tree.unit().validate(validation_logger);

    return emit(tree, validation_logger, out, "tree");
}

/**
 * The second validation steps. Operates on the CFG.
 */
static bool validateFlow(SourceTree& tree, ValidationLogger& validation_logger, std::ostream& out)
{
    tree.unit().validateFlow(validation_logger);

    return emit(tree, validation_logger, out, "flow");
}

static std::filesystem::path getResultPath(std::filesystem::path const& bin_dir, Unit& unit, llvm::Triple const& triple)
{
    return bin_dir / (unit.getName() + unit.getType().getExtension(triple));
}

static bool build(SourceTree&                  tree,
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
    std::filesystem::path const obj = obj_dir / (tree.unit().getName() + ".obj");
    std::filesystem::path const res = getResultPath(bin_dir, tree.unit(), tree.unit().getTargetTriple());

    compiler.compile(ilr);
    compiler.emitObject(obj);

    tree.unit().exportPackage(bin_dir);

    return linker.link(obj, res, out);
}

static Optional<bool> buildProject(Project&              project,
                                   Packages const&       packages,
                                   std::set<std::string> included_packages,
                                   std::ostream&         root_out);

static Optional<Owned<Project>> prepareProject(std::filesystem::path const&           project_file_path,
                                               Optional<std::filesystem::path> const& override_build_dir,
                                               std::ostream&                          out,
                                               Packages const&                        packages)
{
    std::filesystem::path build_dir = project_file_path.parent_path() / "bld";
    if (override_build_dir.hasValue()) build_dir = *override_build_dir;

    std::filesystem::path const project_definition_root = build_dir / "def";
    std::filesystem::path const project_definition_bin  = project_definition_root / "bin";
    std::filesystem::path const project_definition_obj  = project_definition_root / "obj";

    llvm::Triple const          triple(llvm::sys::getDefaultTargetTriple());
    std::filesystem::path const triple_dir = triple.getTriple();
    std::filesystem::path const bin_suffix = triple_dir / "bin";

    ProjectDescription::Description description;
    ValidationLogger                validation_logger;

    bool const directory_fresh =
        !std::filesystem::exists(project_definition_bin) || !std::filesystem::exists(project_definition_obj);

    std::filesystem::create_directories(project_definition_bin);
    std::filesystem::create_directories(project_definition_obj);

    ProjectDescription project_description(project_file_path);

    std::filesystem::path const result = getResultPath(project_definition_bin, project_description, triple);
    project_description.setBinaryDescriptionPath(result);

    SourceTree tree(project_description);

    auto ok = tree.unit().preparePackageDependencies(packages, prepareProject, project_definition_root, out);
    if (!ok) return std::nullopt;

    std::tie(ok, std::ignore) = tree.unit().buildPackageDependencies(packages,
                                                                     buildProject,
                                                                     project_definition_root,
                                                                     project_definition_bin,
                                                                     bin_suffix,
                                                                     directory_fresh,
                                                                     out,
                                                                     {},
                                                                     out);

    if (!ok) return std::nullopt;

    bool const project_description_dirty = tree.isYoungerThan(result);

    if (project_description_dirty)
    {
        tree.parse();

        out << "ance: input: Project file read" << std::endl;

        ok = validateTree(tree, validation_logger, out);
        if (!ok) return std::nullopt;

        project_description.preBuild();

        ok = validateFlow(tree, validation_logger, out);
        if (!ok) return std::nullopt;

        ok = build(tree, triple, project_definition_obj, project_definition_bin, out);
        if (!ok) return std::nullopt;
    }

    ok = project_description.loadDescription();
    if (!ok)
    {
        out << "ance: input: Project description invalid" << std::endl;
        return std::nullopt;
    }

    description = project_description.description();
    return makeOwned<Project>(std::move(description),
                              Application::BuildInfo {
                                  .triple            = triple,
                                  .build_dir         = build_dir,
                                  .triple_dir        = triple_dir,
                                  .bin_suffix        = bin_suffix,
                                  .validation_logger = validation_logger,
                                  .out               = out,
                                                      .project_description_dirty = project_description_dirty});
}

static Optional<bool> buildProject(Project&              project,
                                   Packages const&       packages,
                                   std::set<std::string> included_packages,
                                   std::ostream&         root_out)
{
    Application&            application = project.getApplication();
    Application::BuildInfo& info        = application.getBuildInfo();

    std::filesystem::path const obj_dir = info.build_dir / info.triple_dir / "obj";
    std::filesystem::path const bin_dir = info.build_dir / info.bin_suffix;

    bool const directory_fresh = !std::filesystem::exists(obj_dir) || !std::filesystem::exists(bin_dir);

    std::filesystem::create_directories(obj_dir);
    std::filesystem::create_directories(bin_dir);

    auto ok = application.preparePackageDependencies(packages, prepareProject, info.build_dir, info.out);
    if (!ok) return false;

    size_t built_count = 0;

    std::tie(ok, built_count) = application.buildPackageDependencies(packages,
                                                                     buildProject,
                                                                     info.build_dir,
                                                                     bin_dir,
                                                                     info.bin_suffix,
                                                                     directory_fresh,
                                                                     info.out,
                                                                     std::move(included_packages),
                                                                     root_out);
    if (!ok) return false;

    SourceTree tree(application);

    if (tree.isYoungerThan(getResultPath(bin_dir, application, info.triple)) || built_count > 0
        || info.project_description_dirty)
    {
        size_t const count = tree.parse();

        info.out << "ance: input: " << count << " source file(s) read" << std::endl;

        ok = validateTree(tree, info.validation_logger, info.out);
        if (!ok) return false;

        if (application.isEmittingExtras()) application.emitAsSource(obj_dir / "input.nc");

        application.preBuild();

        if (application.isEmittingExtras()) application.emitAsSource(obj_dir / "input_expanded.nc");

        ok = validateFlow(tree, info.validation_logger, info.out);
        if (!ok) return false;

        ok = build(tree, info.triple, obj_dir, bin_dir, info.out);
        if (!ok) return false;

        info.out << "ance: build: Success" << std::endl;
        return true;
    }
    else
    {
        info.out << "ance: build: Skipped" << std::endl;
        return std::nullopt;
    }
}

static bool run(std::ostream&                          out,
                std::filesystem::path const&           project_file_path,
                Optional<std::filesystem::path> const& override_build_dir,
                Packages const&                        packages)
{
    out << "======================== Build [ " << project_file_path.stem().string()
        << " ] ========================" << std::endl;

    auto project = prepareProject(project_file_path, override_build_dir, out, packages);

    if (project.hasValue()) { return buildProject(**project, packages, {(**project).getName()}, out).valueOr(true); }

    return false;
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "ance: command: Requires exactly one argument" << std::endl;

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
        std::cout << "ance: input: Project file does not exist" << std::endl;
        return EXIT_FAILURE;
    }

    auto ok = run(std::cout, project_file_path, std::nullopt, packages);

    llvm::llvm_shutdown();

    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}
