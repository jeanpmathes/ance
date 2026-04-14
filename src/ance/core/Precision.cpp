#include "Precision.h"

#include <stdexcept>

#include <llvm/ADT/APFloat.h>

ance::core::Precision::operator Value() const
{
    return value_;
}

ance::core::Precision ance::core::Precision::get(llvm::fltSemantics const& semantics)
{
    if (&semantics == &llvm::APFloat::IEEEhalf())
    {
        return HALF;
    }

    if (&semantics == &llvm::APFloat::IEEEsingle())
    {
        return SINGLE;
    }

    if (&semantics == &llvm::APFloat::IEEEdouble())
    {
        return DOUBLE;
    }

    if (&semantics == &llvm::APFloat::IEEEquad())
    {
        return QUAD;
    }

    throw std::logic_error("Invalid fltSemantics");
}

llvm::fltSemantics const& ance::core::Precision::getLlvmSemantics() const
{
    switch (value_)
    {
        case HALF: return llvm::APFloat::IEEEhalf();
        case SINGLE: return llvm::APFloat::IEEEsingle();
        case DOUBLE: return llvm::APFloat::IEEEdouble();
        case QUAD: return llvm::APFloat::IEEEquad();
    }

    throw std::logic_error("Invalid precision");
}

std::string ance::core::Precision::getSuffix() const
{
    switch (value_)
    {
        case HALF: return "h";
        case SINGLE: return "s";
        case DOUBLE: return "d";
        case QUAD: return "q";
    }

    throw std::logic_error("Invalid precision");
}
