#include "OptLevel.h"

OptLevel::operator Value() const
{
    return value_;
}

llvm::CodeGenOptLevel OptLevel::getCodeGenerationOptimizationLevel() const
{
    switch (value_)
    {
        case O_0:
            return llvm::CodeGenOptLevel::None;

        case O_1:
            return llvm::CodeGenOptLevel::Less;

        case O_2:
            return llvm::CodeGenOptLevel::Default;

        case O_3:
            return llvm::CodeGenOptLevel::Aggressive;
    }
}

llvm::OptimizationLevel OptLevel::getOptimizationLevel() const
{
    switch (value_)
    {
        case O_0:
            return llvm::OptimizationLevel::O0;

        case O_1:
            return llvm::OptimizationLevel::O1;

        case O_2:
            return llvm::OptimizationLevel::O2;

        case O_3:
            return llvm::OptimizationLevel::O3;
    }
}

bool OptLevel::isOptimized() const
{
    return value_ != O_0;
}

llvm::DICompileUnit::DebugEmissionKind OptLevel::getDebugEmissionKind() const
{
    switch (value_)
    {
        case O_0:
            return llvm::DICompileUnit::DebugEmissionKind::FullDebug;

        case O_1:
        case O_2:
        case O_3:
            return llvm::DICompileUnit::DebugEmissionKind::NoDebug;
    }
}
