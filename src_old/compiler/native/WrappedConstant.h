#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_WRAPPEDCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_WRAPPEDCONSTANT_H_

#include "Wrapped.h"

#include "lang/construct/Constant.h"

class NativeBuild;

/**
 * A wrapped llvm constant.
 */
class WrappedConstant
    : public lang::Constant
    , public Wrapped
{
  public:
    /**
     * Create a new wrapped constant.
     * @param type The type of the constant.
     * @param constant The llvm constant.
     */
    WrappedConstant(lang::Type const& type, llvm::Constant* constant);
    ~WrappedConstant() override = default;

    [[nodiscard]] llvm::Constant* getConstant() const override;
    [[nodiscard]] llvm::Value*    getContentValue() const override;

  private:
    llvm::Constant* constant_;
};

#endif
