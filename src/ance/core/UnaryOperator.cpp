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
    }

    throw std::logic_error("Invalid unary operator");
}
