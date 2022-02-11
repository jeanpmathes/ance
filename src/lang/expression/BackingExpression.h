#ifndef ANCE_SRC_ANCE_EXPRESSION_BACKINGEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_BACKINGEXPRESSION_H_

#include "BuildableExpression.h"
#include "Expression.h"

/**
 * An interface for expressions that can back a value.
 */
class BackingExpression
    : public virtual Expression
    , public BuildableExpression
{
  protected:
    void doBuild(CompileContext* context) final;

  public:
    /**
     * Get the native value. Must be built before.
     * @return The native value.
     */
    llvm::Value* getNativeValue();

  protected:
    /**
     * Build the native value.
     * @param context The current compile context.
     * @return The native value.
     */
    virtual llvm::Value* buildNativeValue(CompileContext* context) = 0;

  private:
    llvm::Value* native_value_ {nullptr};
};

#endif
