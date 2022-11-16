#ifndef ANCE_SRC_LANG_EXPRESSION_BINARYOPERATION_H_
#define ANCE_SRC_LANG_EXPRESSION_BINARYOPERATION_H_

#include "DelayableExpression.h"

#include "lang/Element.h"

/**
 * A binary operation, taking two operands and returning a result.
 */
class BinaryOperation
    : public DelayableExpression
    , public lang::Element<BinaryOperation, ANCE_CONSTRUCTS>
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

    [[nodiscard]] Expression&          left() const;
    [[nodiscard]] Expression&          right() const;
    [[nodiscard]] lang::BinaryOperator op() const;

  public:
    [[nodiscard]] std::optional<lang::ResolvingHandle<lang::Type>> tryGetType() const override;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

  protected:
    void doBuild(CompileContext& context) override;

  private:
    [[nodiscard]] lang::ResolvingHandle<lang::Type> getRightType() const;
    static lang::ResolvingHandle<lang::Type>        getRightType(lang::BinaryOperator              op,
                                                                 lang::ResolvingHandle<lang::Type> left,
                                                                 lang::ResolvingHandle<lang::Type> right);

  public:
    ~BinaryOperation() override;

  private:
    std::unique_ptr<Expression> left_;
    lang::BinaryOperator        op_;
    std::unique_ptr<Expression> right_;
};

#endif
