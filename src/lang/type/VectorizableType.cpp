#include "VectorizableType.h"

lang::VectorizableType const* lang::VectorizableType::isVectorizable() const
{
    return this;
}

lang::VectorizableType* lang::VectorizableType::isVectorizable()
{
    return this;
}

void lang::VectorizableType::buildRequestedOverload(lang::ResolvingHandle<lang::Type>,
                                                    lang::ResolvingHandle<lang::Type>,
                                                    lang::PredefinedFunction&,
                                                    CompileContext&)
{
    throw std::logic_error("No overloads available for this type");
}
