#include <cassert>

#include "BinaryOperator.h"

lang::BinaryOperator::operator Value() const
{
    return value_;
}

std::string lang::BinaryOperator::toString() const
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

lang::BinaryOperator::Category lang::BinaryOperator::getCategory() const
{
    switch (value_)
    {
        case ADDITION:
        case SUBTRACTION:
        case MULTIPLICATION:
        case DIVISION:
        case REMAINDER:
            return Category::ARITHMETIC;

        case LESS_THAN:
        case LESS_THAN_OR_EQUAL:
        case GREATER_THAN:
        case GREATER_THAN_OR_EQUAL:
            return Category::RELATIONAL;

        case EQUAL:
        case NOT_EQUAL:
            return Category::EQUALITY;

        default:
            assert(false);
    }
}

bool lang::BinaryOperator::isRelational() const
{
    return getCategory() == Category::RELATIONAL;
}

bool lang::BinaryOperator::isEquality() const
{
    return getCategory() == Category::EQUALITY;
}

bool lang::BinaryOperator::isArithmetic() const
{
    return getCategory() == Category::ARITHMETIC;
}
