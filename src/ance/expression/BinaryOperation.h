#ifndef ANCE_SRC_ANCE_EXPRESSION_BINARYOPERATION_H_
#define ANCE_SRC_ANCE_EXPRESSION_BINARYOPERATION_H_

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
                    BinaryOperator              op,
                    std::unique_ptr<Expression> right,
                    ance::Location              location);

  protected:
    void setScope(ance::Scope* scope) override;

  public:
    ance::ResolvingHandle<ance::Type> type() override;

    bool validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~BinaryOperation() override;

  private:
    std::unique_ptr<Expression> left_;
    BinaryOperator              op_;
    std::unique_ptr<Expression> right_;
};

#endif
