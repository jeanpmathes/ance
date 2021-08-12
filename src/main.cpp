#include <filesystem>
#include <iostream>

#include "grammar/anceLexer.h"
#include "grammar/anceParser.h"
#include <antlr4-runtime.h>

#include <llvm/Support/ManagedStatic.h>
#include <llvm/Support/TargetSelect.h>

#include "compiler/AnceCompiler.h"
#include "compiler/AnceLinker.h"
#include "compiler/Visitor.h"
#include "management/File.h"

int main(int argc, char** argv)
{
    if (argc != 3)
    {
        std::cout << "Requires exactly two parameters." << std::endl;

        return EXIT_FAILURE;
    }

    std::filesystem::path project_file(argv[1]);
    data::File            project(project_file);
    project.read();

    Application application(project);

    std::cout << "====== Build [ " << application.getName() << " ] ======" << std::endl;

    std::fstream code;
    code.open(application.getSourceFile());

    antlr4::ANTLRInputStream  input(code);
    anceLexer                 lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    anceParser                parser(&tokens);

    auto visitor = new Visitor(application);

    antlr4::tree::ParseTree* tree = parser.file();
    visitor->visit(tree);

    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmPrinters();
    llvm::InitializeAllAsmPrinters();

    int e;

    if (application.validate())
    {
        AnceCompiler compiler(application);
        AnceLinker   linker(project.root()["link"]);

        std::filesystem::path out_file(argv[2]);

        std::filesystem::path obj_dir = out_file / "obj";
        std::filesystem::path bin_dir = out_file / "bin";

        std::filesystem::create_directory(obj_dir);
        std::filesystem::create_directory(bin_dir);

        std::filesystem::path obj = obj_dir / (application.getName() + ".o");
        std::filesystem::path exe = bin_dir / (application.getName() + ".exe");

        compiler.compile();
        compiler.emitObject(obj);

        linker.link(obj, exe);

        e = EXIT_SUCCESS;
    }
    else
    {
        e = EXIT_FAILURE;
    }

    llvm::llvm_shutdown();

    return e;
}