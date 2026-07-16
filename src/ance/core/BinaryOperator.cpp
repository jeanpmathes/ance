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

        case LESS_THAN:
            return "<";

        case LESS_THAN_OR_EQUAL:
            return "<=";

        case GREATER_THAN:
            return ">";

        case GREATER_THAN_OR_EQUAL:
            return ">=";

        case EQUAL:
            return "==";

        case NOT_EQUAL:
            return "/=";
    }

    throw std::invalid_argument("Invalid binary operator");
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

        case LESS_THAN:
            return "lt";

        case LESS_THAN_OR_EQUAL:
            return "le";

        case GREATER_THAN:
            return "gt";

        case GREATER_THAN_OR_EQUAL:
            return "ge";

        case EQUAL:
            return "eq";

        case NOT_EQUAL:
            return "ne";
    }

    throw std::invalid_argument("Invalid binary operator");
}
