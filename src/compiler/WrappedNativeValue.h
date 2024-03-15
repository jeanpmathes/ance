#ifndef ANCE_SRC_LANG_CONSTRUCT_VALUE_WRAPPEDNATIVEVALUE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VALUE_WRAPPEDNATIVEVALUE_H_

#include "lang/construct/Value.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class NativeBuild;

/**
 * A value wrapping a native value.
 */
class WrappedNativeValue : public lang::Value
{
  public:
    /**
     * Create a new wrapped native value.
     * @param type The type of the value.
     * @param value The native value to wrap.
     * @param native_build The execution context.
     */
    WrappedNativeValue(lang::Type const& type, llvm::Value* value, NativeBuild& native_build);
    ~WrappedNativeValue() override = default;

    Execution::Handle<false> getExecutionValue() override;

  private:
    NativeBuild& native_build_;
    llvm::Value* value_;
};
#endif
