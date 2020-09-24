#include <iostream>
#include <process.h>

#include "antlr4-runtime.h"
#include "anceLexer.h"
#include "anceParser.h"
#include "anceBaseListener.h"

#include "FileListener.h"

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

	system("pause");
}