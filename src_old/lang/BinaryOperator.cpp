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
            return "/=";
        case BITWISE_AND:
            return "<and>";
        case BITWISE_OR:
            return "<or>";
        case BITWISE_XOR:
            return "<xor>";
        case SHIFT_LEFT:
            return "<sl>";
        case SHIFT_RIGHT:
            return "<sr>";
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

        case BITWISE_AND:
        case BITWISE_OR:
        case BITWISE_XOR:
            return Category::BITWISE;

        case SHIFT_LEFT:
        case SHIFT_RIGHT:
            return Category::BITWISE_SHIFT;
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

bool lang::BinaryOperator::isBitwise() const
{
    return getCategory() == Category::BITWISE;
}

bool lang::BinaryOperator::isShift() const
{
    return getCategory() == Category::BITWISE_SHIFT;
}
