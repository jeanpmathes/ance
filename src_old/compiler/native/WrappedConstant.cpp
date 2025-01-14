#include "WrappedConstant.h"

#include "NativeBuild.h"

WrappedConstant::WrappedConstant(lang::Type const& type, llvm::Constant* constant) : Constant(type), constant_(constant)
{}

llvm::Constant* WrappedConstant::getConstant() const
{
    return constant_;
}

llvm::Value* WrappedConstant::getContentValue() const
{
    return constant_;
}
