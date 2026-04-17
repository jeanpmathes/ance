#include "BinaryOperator.h"

#include <stdexcept>

ance::core::BinaryOperator::operator Value() const
{
    return value_;
}

std::string ance::core::BinaryOperator::toString() const
{
    switch (value_)
    {
        case UNSPECIFIED:
            return "/* unspecified */";

        case ADDITION:
            return "+";

        case SUBTRACTION:
            return "-";

        case MULTIPLICATION:
            return "*";

        case DIVISION:
            return "/";

        case REMAINDER:
            return "%";
    }

    throw std::logic_error("Invalid binary operator");
}

std::string ance::core::BinaryOperator::toShortName() const
{
    switch (value_)
    {
        case UNSPECIFIED:
            return "";

        case ADDITION:
            return "add";

        case SUBTRACTION:
            return "sub";

        case MULTIPLICATION:
            return "mul";

        case DIVISION:
            return "div";

        case REMAINDER:
            return "rem";
    }

    throw std::logic_error("Invalid binary operator");
}
