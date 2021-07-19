#include "File.h"

#include <fstream>

#include "management/grammar/dataLexer.h"
#include "management/grammar/dataParser.h"
#include <antlr4-runtime.h>

#include "DataVisitor.h"

data::File::File(const std::filesystem::path& path)
    : path_(path)
{
}

const std::filesystem::path& data::File::path()
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
    data::Element*           element = visitor.visit(tree);
    element_.reset(element);
}

const data::Element& data::File::root()
{
    assert(element_.get() && "Element has to be read before accessing it.");
    return *element_;
}
