#include "Printer.h"

#include "ance/core/Intrinsic.h"

ance::core::Printer::Printer(std::ostream& out) : out_(out) {}

ance::core::Printer::~Printer() = default;

void ance::core::Printer::print(std::string const& text)
{
    indent();
    out_ << text;
}

// todo: maybe just make it generic with concept for when << is defined

void ance::core::Printer::print(char const* text)
{
    indent();
    out_ << text;
}

void ance::core::Printer::print(Identifier const& identifier)
{
    indent();
    out_ << identifier;
}

void ance::core::Printer::print(AccessModifier const access_modifier)
{
    indent();
    out_ << access_modifier.toString();// todo: access modifier should provide operator<<
}

void ance::core::Printer::print(UnaryOperator unary_operator)
{
    indent();
    out_ << unary_operator.toString();// todo: unary operator should provide operator<<
}

void ance::core::Printer::print(Assigner const assigner)
{
    indent();
    out_ << assigner.getSymbol();// todo: assigner should provide operator<<
}

void ance::core::Printer::print(LiteralType literal_type)
{
    indent();
    out_ << literal_type.toString();// todo: literal type should provide operator<<
}

void ance::core::Printer::print(Intrinsic const& intrinsic)
{
    indent();
    out_ << intrinsic;
}

void ance::core::Printer::line()
{
    indent();
    out_ << std::endl;
    in_new_line_ = true;
}

void ance::core::Printer::enter()
{
    indent_level_++;
}

void ance::core::Printer::exit()
{
    indent_level_--;
}

void ance::core::Printer::indent()
{
    if (in_new_line_)
    {
        out_ << std::string(indent_level_ * 4, ' ');
        in_new_line_ = false;
    }
}
