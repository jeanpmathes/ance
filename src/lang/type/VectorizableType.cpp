#include "VectorizableType.h"

lang::VectorizableType const* lang::VectorizableType::isVectorizable() const
{
    return this;
}

lang::VectorizableType* lang::VectorizableType::isVectorizable()
{
    return this;
}

Shared<lang::Value> lang::VectorizableType::buildOperator(lang::BinaryOperator,
                                                          Shared<Value>,
                                                          Shared<Value>,
                                                          lang::ResolvingHandle<lang::Type>,
                                                          CompileContext&)
{
    throw std::runtime_error("No operator available for this type");
}

Shared<lang::Value> lang::VectorizableType::buildOperator(lang::UnaryOperator,
                                                          Shared<Value>,
                                                          lang::ResolvingHandle<lang::Type>,
                                                          CompileContext&)
{
    throw std::runtime_error("No operator available for this type");
}

Shared<lang::Value> lang::VectorizableType::buildCast(lang::ResolvingHandle<lang::Type>,
                                                      Shared<lang::Value>,
                                                      lang::ResolvingHandle<lang::Type>,
                                                      CompileContext&)
{
    throw std::runtime_error("No cast available for this type");
}

void lang::VectorizableType::buildRequestedOverload(lang::ResolvingHandle<lang::Type>,
                                                    lang::ResolvingHandle<lang::Type>,
                                                    lang::PredefinedFunction&,
                                                    CompileContext&)
{
    throw std::runtime_error("No overloads available for this type");
}
