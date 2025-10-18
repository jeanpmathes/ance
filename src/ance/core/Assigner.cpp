#include "Assigner.h"

ance::core::Assigner::operator Value() const
{
    return value_;
}

bool ance::core::Assigner::isFinal() const
{
    return value_ == FINAL_COPY_ASSIGNMENT;
}

bool ance::core::Assigner::hasSymbol() const
{
    return value_ != UNSPECIFIED;
}

std::string ance::core::Assigner::getSymbol() const
{
    if (!hasSymbol())
        return "";

    switch (value_)
    {
        case COPY_ASSIGNMENT:
            return "<:";
        case FINAL_COPY_ASSIGNMENT:
            return ":=";
        case MOVE_ASSIGNMENT:
            return "<-";

        default:
            return "";
    }
}
