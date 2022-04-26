#ifndef ANCE_SRC_LANG_EXPRESSION_UNARYOPERATION_H_
#define ANCE_SRC_LANG_EXPRESSION_UNARYOPERATION_H_

#include "DelayableExpression.h"

#include "lang/Element.h"

/**
 * A unary operation, which is a single operand expression.
 */
class UnaryOperation
    : public DelayableExpression
    , public lang::Element<UnaryOperation, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Creates a new unary operation.
     * @param op The operation.
     * @param operand The operand of the operation.
     * @param location The location of the operation.
     */
    UnaryOperation(lang::UnaryOperator op, std::unique_ptr<Expression> operand, lang::Location location);

    [[nodiscard]] Expression&         operand() const;
    [[nodiscard]] lang::UnaryOperator op() const;

  public:
    lang::ResolvingHandle<lang::Type> type() override;

    bool validate(ValidationLogger& validation_logger) override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~UnaryOperation() override;

  private:
    std::unique_ptr<Expression> operand_;
    lang::UnaryOperator         op_;
};

#endif
