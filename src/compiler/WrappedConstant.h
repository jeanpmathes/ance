#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_WRAPPEDCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_WRAPPEDCONSTANT_H_

#include "lang/construct/Constant.h"

class NativeBuild;

/**
 * A wrapped llvm constant.
 */
class WrappedConstant : public lang::Constant
{
  public:
    /**
     * Create a new wrapped constant.
     * @param type The type of the constant.
     * @param constant The llvm constant.
     * @param native_build The execution context.
     */
    WrappedConstant(lang::Type const& type, llvm::Constant* constant, NativeBuild& native_build);
    ~WrappedConstant() override = default;

    Execution::Handle<true>  getExecutionConstant() override;
    Execution::Handle<false> getExecutionValue() override;

  private:
    NativeBuild&    native_build_;
    llvm::Constant* constant_;
};

#endif
