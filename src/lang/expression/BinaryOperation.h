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
    BinaryOperation(Owned<Expression> left, lang::BinaryOperator op, Owned<Expression> right, lang::Location location);

    [[nodiscard]] Expression const&    left() const;
    [[nodiscard]] Expression const&    right() const;
    [[nodiscard]] lang::BinaryOperator op() const;

  public:
    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type>& type) override;
    void doBuild(CompileContext& context) override;

  private:
    lang::ResolvingHandle<lang::Type> getRightType();
    [[nodiscard]] lang::Type const&   getRightType() const;

    static lang::ResolvingHandle<lang::Type> getRightType(lang::BinaryOperator              op,
                                                          lang::ResolvingHandle<lang::Type> left,
                                                          lang::ResolvingHandle<lang::Type> right);
    static lang::Type const& getRightTypeC(lang::BinaryOperator op, lang::Type const& left, lang::Type const& right);

  public:
    ~BinaryOperation() override;

  private:
    Owned<Expression>    left_;
    lang::BinaryOperator op_;
    Owned<Expression>    right_;
};

#endif
