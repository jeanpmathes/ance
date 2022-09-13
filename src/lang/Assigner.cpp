#include <cassert>

#include "lang/Assigner.h"

lang::Assigner::operator Value() const
{
    return value_;
}

bool lang::Assigner::isFinal() const
{
    return value_ == FINAL_COPY_ASSIGNMENT;
}

bool lang::Assigner::hasSymbol() const
{
    return value_ != REFERENCE_BINDING && value_ != UNSPECIFIED;
}

std::string lang::Assigner::getSymbol() const
{
    assert(hasSymbol());

    switch (value_)
    {
        case COPY_ASSIGNMENT:
            return "<:";
        case MOVE_ASSIGNMENT:
            return "<-";
        case FINAL_COPY_ASSIGNMENT:
            return ":=";

        default:
            return "";
    }
}

