#ifndef ANCE_SRC_LANG_EXPRESSION_BINARYOPERATION_H_
#define ANCE_SRC_LANG_EXPRESSION_BINARYOPERATION_H_

#include "Expression.h"

#include "lang/Element.h"

/**
 * A binary operation, taking two operands and returning a result.
 */
class BinaryOperation
    : public Expression
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
    BinaryOperation(Owned<Expression> left, lang::BinaryOperator op, Owned<Expression> right, lang::Location location);

    [[nodiscard]] Expression const&    left() const;
    [[nodiscard]] Expression const&    right() const;
    [[nodiscard]] lang::BinaryOperator op() const;

  public:
    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  public:
    /**
     * Get the type of the right operand, considering possibly needed implicit conversions.
     * @return The type of the right operand.
     */
    [[nodiscard]] lang::Type const& getRightType() const;

    ~BinaryOperation() override;

  private:
    Owned<Expression>    left_;
    lang::BinaryOperator op_;
    Owned<Expression>    right_;
};

#endif
