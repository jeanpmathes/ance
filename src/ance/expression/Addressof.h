#ifndef ANCE_SRC_ANCE_EXPRESSION_ADDRESSOF_H_
#define ANCE_SRC_ANCE_EXPRESSION_ADDRESSOF_H_

#include "DelayableExpression.h"

#include "compiler/Runtime.h"

class Application;

/**
 * An addressof expression.
 */
class Addressof : public DelayableExpression
{
  public:
    /**
     * Create an addressof expression that provides the address of the arg.
     * @param arg The argument to get the address of.
     * @param location The source location of the expression.
     */
    Addressof(std::unique_ptr<Expression> arg, ance::Location location);

  protected:
    void setScope(ance::Scope* scope) override;

  public:
    ance::Type* type() override;

    bool validate(ValidationLogger& validation_logger) override;

    bool accept(ance::ApplicationVisitor& visitor) override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~Addressof() override;

  private:
    std::unique_ptr<Expression> arg_;
    ance::Type*                 return_type_ {nullptr};
};
#endif