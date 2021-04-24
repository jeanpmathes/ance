#include <iostream>
#include <process.h>
#include <filesystem>

#include "antlr4-runtime.h"
#include "anceLexer.h"
#include "anceParser.h"

#include "llvm/Support/TargetSelect.h"

#include "anceCompiler.h"
#include "Visitor.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        std::cout << "Requires exactly one parameter." << std::endl;

        return EXIT_FAILURE;
    }

    std::filesystem::path proj_file(argv[1]);

    std::ifstream t(proj_file);
    std::stringstream buffer;
    buffer << t.rdbuf();

    std::filesystem::path code_file = std::filesystem::path(proj_file);
    code_file.replace_filename(buffer.str());

    std::fstream code;
    code.open(code_file);

    antlr4::ANTLRInputStream input(code);
    anceLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    anceParser parser(&tokens);

    Application application(proj_file, code_file);
    auto visitor = new Visitor(application);

    antlr4::tree::ParseTree* tree = parser.file();
    visitor->visit(tree);

    llvm::InitializeAllTargetInfos();
    llvm::InitializeAllTargets();
    llvm::InitializeAllTargetMCs();
    llvm::InitializeAllAsmPrinters();
    llvm::InitializeAllAsmPrinters();

    if (application.validate())
    {
        anceCompiler compiler(application);
        compiler.compile(std::filesystem::path(R"(C:\Users\jeanp\source\repos\ance\ance_output)"));

        return EXIT_SUCCESS;
    }
    else
    {
        return EXIT_FAILURE;
    }
}