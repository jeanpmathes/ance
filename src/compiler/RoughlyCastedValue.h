#ifndef ANCE_SRC_LANG_CONSTRUCT_VALUE_ROUGHLYCASTEDVALUE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VALUE_ROUGHLYCASTEDVALUE_H_

#include "lang/construct/Value.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class NativeBuild;

/**
 * Create a value that is result of a rough as.
 */
class RoughlyCastedValue : public lang::Value
{
  public:
    /**
     * Create a new roughly casted value.
     * @param target_type The target type.
     * @param original The original value.
     * @param native_build The execution context.
     */
    RoughlyCastedValue(lang::Type const& target_type, Shared<lang::Value> original, NativeBuild& native_build);

    Execution::Handle<false> getExecutionValue() override;

  private:
    Shared<lang::Value> original_;
};

#endif
