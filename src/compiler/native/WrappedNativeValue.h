#ifndef ANCE_SRC_LANG_CONSTRUCT_VALUE_WRAPPEDNATIVEVALUE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VALUE_WRAPPEDNATIVEVALUE_H_

#include "Wrapped.h"

#include "lang/construct/Value.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class NativeBuild;

/**
 * A value wrapping a native value.
 */
class WrappedNativeValue
    : public lang::Value
    , public Wrapped
{
  public:
    /**
     * Create a new wrapped native value.
     * @param type The type of the value.
     * @param value The native value to wrap.
     */
    WrappedNativeValue(lang::Type const& type, llvm::Value* value);
    ~WrappedNativeValue() override = default;

    [[nodiscard]] llvm::Value* getNativeValue() const override;

  private:
    llvm::Value* value_;
};
#endif
