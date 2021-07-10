#ifndef ANCE_SRC_ANCE_EXPRESSION_DEFAULTVALUEEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_DEFAULTVALUEEXPRESSION_H_

#include "BackingConstantExpression.h"

#include "ExpressionBackedConstant.h"

class DefaultValueExpression : public BackingConstantExpression
{
  public:
    explicit DefaultValueExpression(ance::Type* type);

    ance::Type* getType() override;

    ance::Value* getValue() override;

    ance::Constant* getConstantValue() override;

    llvm::Constant* buildContentConstant(llvm::LLVMContext& c) override;

    ~DefaultValueExpression() override;

  private:
    ance::Type*     type_;
    ance::Constant* constant_ {new ance::ExpressionBackedConstant(this)};
};

#endif