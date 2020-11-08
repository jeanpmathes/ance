#include <iostream>
#include <process.h>

#include "antlr4-runtime.h"
#include "anceLexer.h"
#include "anceParser.h"
#include "anceBaseListener.h"

#include "llvm/Support/TargetSelect.h"

#include "FileListener.h"
#include "anceCompiler.h"

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
	FileListener listener(application);

	antlr4::tree::ParseTree* tree = parser.file();
	antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

	llvm::InitializeAllTargetInfos();
	llvm::InitializeAllTargets();
	llvm::InitializeAllTargetMCs();
	llvm::InitializeAllAsmPrinters();
	llvm::InitializeAllAsmPrinters();

	if (application.Validate())
	{
		anceCompiler compiler(application);
		compiler.Compile(std::filesystem::path("C:\\Users\\jeanp\\source\\repos\\ance\\ance_output"));

		return EXIT_SUCCESS;
	}
	else
	{
		return EXIT_FAILURE;
	}
}