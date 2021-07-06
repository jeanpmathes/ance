#include <iostream>
#include <filesystem>

#include <antlr4-runtime.h>
#include "anceLexer.h"
#include "anceParser.h"

#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/ManagedStatic.h>

#include "File.h"
#include "AnceCompiler.h"
#include "AnceLinker.h"
#include "Visitor.h"

int main(int argc, char** argv)
{
	if (argc != 3)
	{
		std::cout << "Requires exactly two parameters." << std::endl;

		return EXIT_FAILURE;
	}

	std::filesystem::path project_file(argv[1]);
	data::File project(project_file);
	project.read();

	Application application(project);

	std::cout << "====== Build [ " << application.getName() << " ] ======" << std::endl;

	std::fstream code;
	code.open(application.getSourceFile());

	antlr4::ANTLRInputStream input(code);
	anceLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	anceParser parser(&tokens);

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
		AnceLinker linker(project.root()["link"]);

		std::filesystem::path out_file(argv[2]);

		std::filesystem::path bc_dir = out_file / "bc";
		std::filesystem::path bin_dir = out_file / "bin";

		std::filesystem::create_directory(bc_dir);
		std::filesystem::create_directory(bin_dir);

		std::filesystem::path bc = bc_dir / (application.getName() + ".bc");
		std::filesystem::path exe = bin_dir / (application.getName() + ".exe");

		compiler.compile(bc);
		linker.link(bc, exe);

		e = EXIT_SUCCESS;
	}
	else
	{
		e = EXIT_FAILURE;
	}

	llvm::llvm_shutdown();

	return e;
}