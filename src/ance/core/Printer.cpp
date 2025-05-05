#include "Printer.h"

#include "ance/core/Intrinsic.h"
#include "ance/core/Function.h"

ance::core::Printer::Printer(std::ostream& out) : out_(out) {}

ance::core::Printer::~Printer() = default;

void ance::core::Printer::print(std::string const& text)
{
    indent();
    out_ << text;
}

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

void ance::core::Printer::print(Intrinsic const& intrinsic)
{
    indent();
    out_ << intrinsic;
}

void ance::core::Printer::print(Function const& function)
{
    indent();
    out_ << function;
}

void ance::core::Printer::print(size_t const value)
{
    indent();
    out_ << value;
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
