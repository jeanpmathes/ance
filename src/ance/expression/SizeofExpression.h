#ifndef ANCE_SRC_ANCE_EXPRESSION_SIZEOFEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_SIZEOFEXPRESSION_H_

#include "BackingExpression.h"

#include "ExpressionBackedValue.h"

class Application;

class SizeofExpression : public BackingExpression
{
  public:
    explicit SizeofExpression(Expression* expression);

    void setScope(ance::Scope* scope) override;

    ance::Type* type() override;

    ance::Value* getValue() override;

    llvm::Value* buildNativeValue(CompileContext* context) override;

  private:
    ance::Value* return_value_ {new ance::ExpressionBackedValue(this)};
    Expression*  expression_;
};

#endif