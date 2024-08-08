#ifndef ANCE_SRC_LANG_CONSTRUCT_VALUE_WRAPPEDCONTENTVALUE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VALUE_WRAPPEDCONTENTVALUE_H_

#include "Wrapped.h"

#include "lang/construct/Value.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class NativeBuild;

/**
 * A value wrapping a content value.
 */
class WrappedContentValue
    : public lang::Value
    , public Wrapped
{
  public:
    /**
     * Create a new wrapped native value.
     * @param type The type of the value.
     * @param value The native value to wrap.
     */
    WrappedContentValue(lang::Type const& type, llvm::Value* value);
    ~WrappedContentValue() override = default;

    [[nodiscard]] llvm::Value* getContentValue() const override;

  private:
    llvm::Value* value_;
};

#endif
