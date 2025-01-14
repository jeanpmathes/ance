#ifndef ANCE_SRC_COMPILER_NATIVE_WRAPPED_H_
#define ANCE_SRC_COMPILER_NATIVE_WRAPPED_H_

namespace llvm
{
    class Value;
    class Constant;
}

/**
 * Interface that allows to unwrap the wrapped values and constants.
 */
class Wrapped
{
  public:
    virtual ~Wrapped() = default;

    [[nodiscard]] virtual llvm::Value*    getNativeValue() const;
    [[nodiscard]] virtual llvm::Value*    getContentValue() const;
    [[nodiscard]] virtual llvm::Constant* getConstant() const;
};

#endif
