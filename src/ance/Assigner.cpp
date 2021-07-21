#include "Assigner.h"

Assigner::operator Value() const
{
    return value_;
}

bool Assigner::isFinal()
{
    return value_ == FINAL_COPY_ASSIGNMENT;
}
