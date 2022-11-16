#include "File.h"

#include <fstream>

#include "management/grammar/dataLexer.h"
#include "management/grammar/dataParser.h"
#include <antlr4-runtime.h>

#include "DataVisitor.h"

data::File::File(std::filesystem::path const& path) : path_(path) {}

std::filesystem::path const& data::File::path()
{
    return path_;
}

void data::File::read()
{
    std::fstream code;
    code.open(path_);

    antlr4::ANTLRInputStream  input(code);
    dataLexer                 lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    dataParser                parser(&tokens);

    DataVisitor visitor;

    antlr4::tree::ParseTree* tree    = parser.element();
    data::Element*           element = any_cast<data::Element*>(visitor.visit(tree));
    element_.reset(element);
}

data::Element const& data::File::root()
{
    assert(element_.get() && "Element has to be read before accessing it.");
    return *element_;
}
