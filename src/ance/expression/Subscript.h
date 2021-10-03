#ifndef ANCE_SRC_ANCE_EXPRESSION_SUBSCRIPT_H_
#define ANCE_SRC_ANCE_EXPRESSION_SUBSCRIPT_H_

#include "DelayableExpression.h"

/**
 * A subscript operation.
 */
class Subscript : public DelayableExpression
{
  public:
    /**
     * Create a new subscript access.
     * @param indexed The indexed value.
     * @param index The index to use.
     * @param location The source location.
     */
    Subscript(Expression* indexed, Expression* index, ance::Location location);

  protected:
    void setScope(ance::Scope* scope) override;

  public:
    ance::Type* type() override;

    bool validate(ValidationLogger& validation_logger) override;

    bool accept(ance::ApplicationVisitor& visitor) override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~Subscript() override;

  private:
    Expression* indexed_;
    Expression* index_;
};

#endif