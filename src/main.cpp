#include <filesystem>
#include <iostream>

#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>

#include <boost/locale.hpp>

#include "compiler/AnceCompiler.h"
#include "compiler/AnceLinker.h"
#include "compiler/Application.h"
#include "compiler/Project.h"
#include "compiler/SourceTree.h"
#include "compiler/SourceVisitor.h"
#include "lang/ApplicationVisitor.h"
#include "management/File.h"
#include "validation/ValidationLogger.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "ance: command: Requires exactly one parameter." << std::endl;

        return EXIT_FAILURE;
    }

    boost::locale::generator gen;
    std::locale::global(gen(""));

    std::filesystem::path project_file_path(argv[1]);
    data::File            project_file(project_file_path);
    project_file.read();

    Project project(project_file);

    Application& application = project.getApplication();

    std::cout << "============ Build [ " << project.getName() << " ] ============" << std::endl;

    SourceTree tree(application);
    size_t     count = tree.parse();

    std::cout << "ance: input: " << count << " source file(s) read" << std::endl;

    size_t fatal_syntax_error_count = tree.emitMessages();

    if (fatal_syntax_error_count == 0)
    {
        SourceVisitor source_visitor(application);
        tree.accept(source_visitor);

        application.preValidate();

        ValidationLogger validation_logger;

        application.validate(validation_logger);

        if (validation_logger.errorCount() == 0)
        {
            std::filesystem::path out_dir = project_file_path.parent_path() / "out";

            std::filesystem::path obj_dir = out_dir / "obj";
            std::filesystem::path bin_dir = out_dir / "bin";

            application.emitAsSource(obj_dir / "input.nc");
            application.preBuild();
            application.emitAsSource(obj_dir / "input_prebuild.nc");

            application.validateFlow(validation_logger);

            if (validation_logger.errorCount() == 0)
            {
                validation_logger.emitMessages(tree.getSourceFiles());

                llvm::InitializeAllTargetInfos();
                llvm::InitializeAllTargets();
                llvm::InitializeAllTargetMCs();
                llvm::InitializeAllAsmParsers();
                llvm::InitializeAllAsmPrinters();

                AnceCompiler compiler(application, tree);
                AnceLinker   linker(project_file.root()["link"]);

                std::filesystem::create_directory(obj_dir);
                std::filesystem::create_directory(bin_dir);

                std::filesystem::path ilr = obj_dir / (project.getName() + ".ll");
                std::filesystem::path obj = obj_dir / (project.getName() + ".o");
                std::filesystem::path exe = bin_dir / (project.getName() + ".exe");

                compiler.compile(ilr);
                compiler.emitObject(obj);

                bool ok = linker.link(obj, exe);

                llvm::llvm_shutdown();

                return ok ? EXIT_SUCCESS : EXIT_FAILURE;
            }
            else { validation_logger.emitMessages(tree.getSourceFiles()); }
        }
        else { validation_logger.emitMessages(tree.getSourceFiles()); }
    }

    return EXIT_FAILURE;
}
