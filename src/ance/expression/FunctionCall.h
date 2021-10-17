#ifndef ANCE_SRC_ANCE_EXPRESSION_FUNCTIONCALL_H_
#define ANCE_SRC_ANCE_EXPRESSION_FUNCTIONCALL_H_

#include "DelayableExpression.h"

namespace ance
{
    class Scope;
}

/**
 * A call to a function.
 */
class FunctionCall : public DelayableExpression
{
  public:
    /**
     * Create a new function call.
     * @param identifier The identifier of the function to call.
     * @param arguments The arguments to pass to the called function.
     * @param location The source location.
     */
    FunctionCall(std::string identifier, std::vector<std::unique_ptr<Expression>> arguments, ance::Location location);

  protected:
    void setScope(ance::Scope* scope) override;

  public:
    ance::Type* type() override;

    bool validate(ValidationLogger& validation_logger) override;

    bool accept(ance::ApplicationVisitor& visitor) override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~FunctionCall() override;

  private:
    std::string                              identifier_;
    std::vector<std::unique_ptr<Expression>> arguments_;
    ance::Scope*                             scope_ {nullptr};
};

#endif