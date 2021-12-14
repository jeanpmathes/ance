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
     * @param function_group The function group to call.
     * @param arguments The arguments to pass to the called function.
     * @param location The source location.
     */
    FunctionCall(ance::ResolvingHandle<ance::FunctionGroup> function_group,
                 std::vector<std::unique_ptr<Expression>>   arguments,
                 ance::Location                             location);

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
    std::optional<ance::ResolvingHandle<ance::Function>> function();

    ance::ResolvingHandle<ance::FunctionGroup>           function_group_;
    std::vector<std::unique_ptr<Expression>>             arguments_;
    bool                                                 overload_resolved_ {false};
    std::optional<ance::ResolvingHandle<ance::Function>> function_ {};
};

#endif