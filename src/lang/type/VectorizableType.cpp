#include "VectorizableType.h"

lang::VectorizableType const* lang::VectorizableType::isVectorizable() const
{
    return this;
}

lang::VectorizableType* lang::VectorizableType::isVectorizable()
{
    return this;
}

void lang::VectorizableType::buildRequestedOverload(lang::Type const&,
                                                    lang::Type const&,
                                                    lang::PredefinedFunction&,
                                                    Execution&) const
{
    throw std::logic_error("No overloads available for this type");
}
