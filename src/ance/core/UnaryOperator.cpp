#include "UnaryOperator.h"

#include <stdexcept>

ance::core::UnaryOperator::operator Value() const
{
    return value_;
}

std::string ance::core::UnaryOperator::toString() const
{
    switch (value_)
    {
        case UNSPECIFIED:
            return "/* unspecified */";

        case NOT:
            return "not";

        case BITWISE_NOT:
            return "<not>";

        case NEGATION:
            return "-";
    }

    throw std::logic_error("Invalid unary operator");
}

std::string ance::core::UnaryOperator::toShortName() const
{
    switch (value_)
    {
        case UNSPECIFIED:
            return "";

        case NOT:
            return "not";

        case BITWISE_NOT:
            return "bitnot";

        case NEGATION:
            return "neg";
    }

    throw std::logic_error("Invalid unary operator");
}
