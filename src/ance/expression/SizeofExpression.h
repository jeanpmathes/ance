#ifndef ANCE_SRC_ANCE_EXPRESSION_SIZEOFEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_SIZEOFEXPRESSION_H_

#include "BackingExpression.h"

#include "ance/construct/value/ExpressionBackedValue.h"

class Application;

/**
 * Gives the size of a value returned by an expression.
 */
class SizeofExpression : public BackingExpression
{
  public:
    /**
     * Create a new sizeof expression expression.
     * @param expression The expression to get the size of.
     */
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