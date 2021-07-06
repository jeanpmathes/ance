#include <lld/Common/Driver.h>
#include "AnceLinker.h"

AnceLinker::AnceLinker(std::optional<std::reference_wrapper<const data::Element>> link_config)
{

}

void AnceLinker::link(const std::filesystem::path& bc, const std::filesystem::path& exe)
{
	std::vector<const char*> args;
	args.push_back("lld");

	args.push_back("/verbose");

	args.push_back("/debug:FULL");

	args.push_back("/machine:x64");
	args.push_back("/subsystem:windows");

	args.push_back("/defaultlib:kernel32");

	args.push_back(R"(/libpath:C:\Program Files (x86)\Windows Kits\10\Lib\10.0.19041.0\um\x64)");

	args.push_back("/entry:_start");

	// string copy not wanted, but necessary as bc.string().c_str() did not work - string was corrupted after passing it to link.
	// todo: a more elegant solution should be found!
	std::string out = "/out:" + exe.string();
	char output[out.size() + 1];
	strcpy(output, out.c_str());

	char input[bc.string().size() + 1];
	strcpy(input, bc.string().c_str());

	args.push_back(output);
	args.push_back(input);

	lld::coff::link(args, false, llvm::outs(), llvm::errs());
}
