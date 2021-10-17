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
     * @param location The source location.
     */
    SizeofExpression(std::unique_ptr<Expression> expression, ance::Location location);

  protected:
    void setScope(ance::Scope* scope) override;

  public:
    ance::Type* type() override;

    bool validate(ValidationLogger& validation_logger) override;

    [[nodiscard]] ance::Value* getValue() const override;

    bool accept(ance::ApplicationVisitor& visitor) override;

  protected:
    llvm::Value* buildNativeValue(CompileContext* context) override;

  private:
    ance::Value*                return_value_ {new ance::ExpressionBackedValue(this)};
    std::unique_ptr<Expression> expression_;
};

#endif