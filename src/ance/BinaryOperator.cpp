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

bool BinaryOperator::isRelational() const
{
    switch (value_)
    {
        case ADDITION:
        case SUBTRACTION:
        case MULTIPLICATION:
        case DIVISION:
        case REMAINDER:
            return false;

        case LESS_THAN:
        case LESS_THAN_OR_EQUAL:
        case GREATER_THAN:
        case GREATER_THAN_OR_EQUAL:
        case EQUAL:
        case NOT_EQUAL:
            return true;

        default:
            assert(false);
            return false;
    }
}

bool BinaryOperator::isArithmetic() const
{
    switch (value_)
    {
        case ADDITION:
        case SUBTRACTION:
        case MULTIPLICATION:
        case DIVISION:
        case REMAINDER:
            return true;

        case LESS_THAN:
        case LESS_THAN_OR_EQUAL:
        case GREATER_THAN:
        case GREATER_THAN_OR_EQUAL:
        case EQUAL:
        case NOT_EQUAL:
            return false;

        default:
            assert(false);
            return false;
    }
}
