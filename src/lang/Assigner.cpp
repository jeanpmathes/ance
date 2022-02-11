#include "lang/Assigner.h"

lang::Assigner::operator Value() const
{
    return value_;
}

bool lang::Assigner::isFinal()
{
    return value_ == FINAL_COPY_ASSIGNMENT;
}

bool lang::Assigner::hasSymbol()
{
    return value_ != REFERENCE_BINDING && value_ != UNSPECIFIED;
}
