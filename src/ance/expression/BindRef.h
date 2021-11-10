#ifndef ANCE_SRC_ANCE_EXPRESSION_BINDREF_H_
#define ANCE_SRC_ANCE_EXPRESSION_BINDREF_H_

#include "DelayableExpression.h"

#include <optional>

class Application;

class BindRef : public DelayableExpression
{
  public:
    /**
     * Get an expression returning a reference to a given value.
     */
    static std::unique_ptr<BindRef> refer(std::unique_ptr<Expression> value, ance::Location location);
    /**
     * Get an expression returning a reference to a value at a given address.
     */
    static std::unique_ptr<BindRef> referTo(std::unique_ptr<Expression> address, ance::Location location);

  private:
    BindRef(std::unique_ptr<Expression> address, ance::Location location);

  protected:
    void setScope(ance::Scope* scope) override;

  public:
    ance::ResolvingHandle<ance::Type> type() override;

    bool validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~BindRef() override;

  private:
    std::unique_ptr<Expression> address_;

    std::optional<ance::ResolvingHandle<ance::Type>> type_ {};
};

#endif
