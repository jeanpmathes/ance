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

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "ance-c: command: Requires exactly two parameters." << std::endl;

        return EXIT_FAILURE;
    }

    std::filesystem::path project_file(argv[1]);
    data::File            project(project_file);
    project.read();

    Application application(project);
    SourceFile  source_file(application.getSourceFile());

    std::cout << "============ Build [ " << application.getName() << " ] ============" << std::endl;

    std::fstream code;
    code.open(application.getSourceFile());

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

        application.globalScope().resolve();

        ValidationLogger validation_logger;
        application.validate(validation_logger);
        validation_logger.emitMessages(source_file);

        if (validation_logger.errorCount() == 0)
        {
            llvm::InitializeAllTargetInfos();
            llvm::InitializeAllTargets();
            llvm::InitializeAllTargetMCs();
            llvm::InitializeAllAsmParsers();
            llvm::InitializeAllAsmPrinters();

            AnceCompiler compiler(application);
            AnceLinker   linker(project.root()["link"]);

            std::filesystem::path out_dir(argv[2]);

            std::filesystem::path obj_dir = out_dir / "obj";
            std::filesystem::path bin_dir = out_dir / "bin";

            std::filesystem::create_directory(obj_dir);
            std::filesystem::create_directory(bin_dir);

            std::filesystem::path ilr = obj_dir / (application.getName() + ".ll");
            std::filesystem::path obj = obj_dir / (application.getName() + ".o");
            std::filesystem::path exe = bin_dir / (application.getName() + ".exe");

            compiler.compile(ilr);
            compiler.emitObject(obj);

            linker.link(obj, exe);

            llvm::llvm_shutdown();

            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}