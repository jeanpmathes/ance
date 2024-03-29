#include <cassert>

#include "UnaryOperator.h"

lang::UnaryOperator::operator Value() const
{
    return value_;
}

std::string lang::UnaryOperator::toString() const
{
    switch (value_)
    {
        case NOT:
            return "not";

        case BITWISE_NOT:
            return "<not>";

        case NEGATION:
            return "-";
    }
}
