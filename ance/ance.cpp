#include <iostream>
#include <process.h>

#include "antlr4-runtime.h"
#include "anceLexer.h"
#include "anceParser.h"
#include "anceBaseListener.h"

#include "llvm/Support/TargetSelect.h"

#include "FileListener.h"
#include "anceCompiler.h"

int main()
{
	std::string code = "return ;";
	std::istringstream stream(code);

	antlr4::ANTLRInputStream input(stream);
	anceLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	anceParser parser(&tokens);

	Application application;
	FileListener listener(application);

	antlr4::tree::ParseTree* tree = parser.file();
	antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);

	llvm::InitializeAllTargetInfos();
	llvm::InitializeAllTargets();
	llvm::InitializeAllTargetMCs();
	llvm::InitializeAllAsmPrinters();
	llvm::InitializeAllAsmPrinters();

	anceCompiler compiler;
	compiler.Compile(application, std::filesystem::path("C:\\Users\\jeanp\\source\\repos\\ance\\ance_output"));

	system("pause");
}