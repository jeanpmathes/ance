#include <filesystem>
#include <iostream>

#include "grammar/anceLexer.h"
#include "grammar/anceParser.h"
#include <antlr4-runtime.h>

#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>

#include "compiler/AnceCompiler.h"
#include "compiler/AnceLinker.h"
#include "compiler/Application.h"
#include "compiler/SourceVisitor.h"
#include "management/File.h"
#include "validation/AnceSyntaxErrorHandler.h"
#include "validation/SourceFile.h"
#include "validation/ValidationLogger.h"
#include "compiler/Project.h"

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "ance-c: command: Requires exactly two parameters." << std::endl;

        return EXIT_FAILURE;
    }

    std::filesystem::path project_file_path(argv[1]);
    data::File            project_file(project_file_path);
    project_file.read();

    Project project(project_file);

    Application& application = project.getApplication();
    SourceFile   source_file(project.getSourceFile());

    std::cout << "============ Build [ " << project.getName() << " ] ============" << std::endl;

    std::fstream code;
    code.open(project.getSourceFile());

    AnceSyntaxErrorHandler syntax_error_listener;

    antlr4::ANTLRInputStream input(code);
    anceLexer                lexer(&input);
    lexer.removeErrorListeners();
    lexer.addErrorListener(syntax_error_listener.lexerErrorListener());

    antlr4::CommonTokenStream tokens(&lexer);
    anceParser                parser(&tokens);
    parser.removeErrorListeners();
    parser.addErrorListener(syntax_error_listener.parserErrorListener());

    auto source_visitor = new SourceVisitor(application);

    antlr4::tree::ParseTree* tree = parser.file();
    syntax_error_listener.emitMessages(source_file);

    if (syntax_error_listener.fatalSyntaxErrorCount() == 0)
    {
        source_visitor->visit(tree);

        application.preValidate();

        ValidationLogger validation_logger;

        application.validate(validation_logger);

        if (validation_logger.errorCount() == 0)
        {
            std::filesystem::path out_dir(argv[2]);

            std::filesystem::path obj_dir = out_dir / "obj";
            std::filesystem::path bin_dir = out_dir / "bin";

            application.emitAsSource(obj_dir / "input.nc");
            application.preBuild();
            application.emitAsSource(obj_dir / "input_prebuilt.nc");

            application.validateFlow(validation_logger);

            if (validation_logger.errorCount() == 0)
            {
                validation_logger.emitMessages(source_file);

                llvm::InitializeAllTargetInfos();
                llvm::InitializeAllTargets();
                llvm::InitializeAllTargetMCs();
                llvm::InitializeAllAsmParsers();
                llvm::InitializeAllAsmPrinters();

                AnceCompiler compiler(application);
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
            else {
                validation_logger.emitMessages(source_file);
            }
        }
        else {
            validation_logger.emitMessages(source_file);
        }
    }

    return EXIT_FAILURE;
}