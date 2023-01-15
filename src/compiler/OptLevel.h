#ifndef ANCE_SRC_COMPILER_OPTLEVEL_H_
#define ANCE_SRC_COMPILER_OPTLEVEL_H_

#include <llvm/Passes/OptimizationLevel.h>
#include <llvm/Support/CodeGen.h>

/**
 * The optimization level.
 */
class OptLevel
{
  public:
    enum Value
    {
        O_0,
        O_1,
        O_2,
        O_3
    };

    OptLevel() = default;
    constexpr OptLevel(Value val) : value_(val) {}// NOLINT(google-explicit-constructor)

             operator Value() const;// NOLINT(google-explicit-constructor)
    explicit operator bool() = delete;

    [[nodiscard]] llvm::CodeGenOpt::Level getCodeGenerationOptimizationLevel() const;
    [[nodiscard]] llvm::OptimizationLevel getOptimizationLevel() const;

  private:
    Value value_;
};

#endif
