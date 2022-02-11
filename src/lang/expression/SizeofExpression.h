#ifndef ANCE_SRC_ANCE_EXPRESSION_SIZEOFEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_SIZEOFEXPRESSION_H_

#include "BackingExpression.h"

#include "lang/construct/value/ExpressionBackedValue.h"

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
    SizeofExpression(std::unique_ptr<Expression> expression, lang::Location location);

  protected:
    void setScope(lang::Scope* scope) override;

  public:
    lang::ResolvingHandle<lang::Type> type() override;

    bool validate(ValidationLogger& validation_logger) override;

    [[nodiscard]] std::shared_ptr<lang::Value> getValue() const override;

  protected:
    llvm::Value* buildNativeValue(CompileContext* context) override;

  private:
    std::shared_ptr<lang::Value> return_value_ {std::make_shared<lang::ExpressionBackedValue>(this)};
    std::unique_ptr<Expression>  expression_;
};

#endif