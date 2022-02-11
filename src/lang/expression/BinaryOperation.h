#ifndef ANCE_SRC_LANG_EXPRESSION_BINARYOPERATION_H_
#define ANCE_SRC_LANG_EXPRESSION_BINARYOPERATION_H_

#include "DelayableExpression.h"

/**
 * A binary operation, taking two operands and returning a result.
 */
class BinaryOperation : public DelayableExpression
{
  public:
    /**
     * Create a binary operation.
     * @param left The left operand.
     * @param op The operator.
     * @param right The right operand.
     * @param location The source location of the operation.
     */
    BinaryOperation(std::unique_ptr<Expression> left,
                    lang::BinaryOperator        op,
                    std::unique_ptr<Expression> right,
                    lang::Location              location);

  protected:
    void setScope(lang::Scope* scope) override;

  public:
    lang::ResolvingHandle<lang::Type> type() override;

    bool validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~BinaryOperation() override;

  private:
    std::unique_ptr<Expression> left_;
    lang::BinaryOperator        op_;
    std::unique_ptr<Expression> right_;
};

#endif
