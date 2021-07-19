#ifndef ANCE_SRC_ANCE_EXPRESSION_BACKINGEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_BACKINGEXPRESSION_H_

#include "Expression.h"

#include "ance/expression/BuildableExpression.h"

class BackingExpression : public virtual Expression
    , public BuildableExpression
{
  public:
    void buildBackingValue(CompileContext* context);

    void build(CompileContext* context) final;

    llvm::Value* getNativeValue();

  protected:
    virtual llvm::Value* buildNativeValue(CompileContext* context) = 0;

  private:
    llvm::Value* native_value_ {nullptr};
};

#endif
