#include <cassert>

#include "BinaryOperator.h"

BinaryOperator::operator Value() const
{
    return value_;
}

std::string BinaryOperator::toString() const
{
    switch (value_)
    {
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

        default:
            assert(false);
            return "";
    }
}
