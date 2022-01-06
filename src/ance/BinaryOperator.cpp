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
            return "!=";

        default:
            assert(false);
            return "";
    }
}
