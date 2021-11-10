#ifndef ANCE_SRC_ANCE_EXPRESSION_FUNCTIONCALL_H_
#define ANCE_SRC_ANCE_EXPRESSION_FUNCTIONCALL_H_

#include "DelayableExpression.h"

#include "ance/construct/Function.h"
#include "ance/utility/ResolvingHandle.h"

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
     * @param function The function to call.
     * @param arguments The arguments to pass to the called function.
     * @param location The source location.
     */
    FunctionCall(ance::ResolvingHandle<ance::Function>    function,
                 std::vector<std::unique_ptr<Expression>> arguments,
                 ance::Location                           location);

  protected:
    void setScope(ance::Scope* scope) override;

  public:
    ance::ResolvingHandle<ance::Type> type() override;

    bool validate(ValidationLogger& validation_logger) override;



  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~FunctionCall() override;

  private:
    ance::ResolvingHandle<ance::Function>    function_;
    std::vector<std::unique_ptr<Expression>> arguments_;
};

#endif