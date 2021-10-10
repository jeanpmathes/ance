#ifndef ANCE_SRC_ANCE_EXPRESSION_BINDREF_H_
#define ANCE_SRC_ANCE_EXPRESSION_BINDREF_H_

#include "DelayableExpression.h"

class Application;

class BindRef : public DelayableExpression
{
  public:
    /**
     * Get an expression returning a reference to a given value.
     */
    static BindRef* refer(Expression* value, Application& app, ance::Location location);
    /**
     * Get an expression returning a reference to a value at a given address.
     */
    static BindRef* referTo(Expression* address, ance::Location location);

  private:
    BindRef(Expression* address, ance::Location location);

  protected:
    void setScope(ance::Scope* scope) override;

  public:
    ance::Type* type() override;

    bool validate(ValidationLogger& validation_logger) override;

    bool accept(ance::ApplicationVisitor& visitor) override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~BindRef() override;

  private:
    Expression*  address_;

    ance::Type* type_ {nullptr};
};

#endif
