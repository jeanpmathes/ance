#include "Assigner.h"

Assigner::operator Value() const
{
    return value_;
}

bool Assigner::isFinal()
{
    return value_ == FINAL_COPY_ASSIGNMENT;
}

bool Assigner::hasSymbol()
{
    return value_ != REFERENCE_BINDING && value_ != UNSPECIFIED;
}
