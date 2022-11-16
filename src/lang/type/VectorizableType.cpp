#include "VectorizableType.h"

lang::VectorizableType const* lang::VectorizableType::isVectorizable() const
{
    return this;
}

lang::VectorizableType* lang::VectorizableType::isVectorizable()
{
    return this;
}
