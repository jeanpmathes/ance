#include "WrappedConstant.h"

#include "NativeBuild.h"

WrappedConstant::WrappedConstant(lang::Type const& type, llvm::Constant* constant, NativeBuild& native_build)
    : Constant(type)
    , native_build_(native_build)
    , constant_(constant)
{}

Execution::Handle<false> WrappedConstant::getExecutionValue()
{
    return native_build_.allocateContentValue(constant_);
}

Execution::Handle<true> WrappedConstant::getExecutionConstant()
{
    return native_build_.allocateConstant(constant_);
}
