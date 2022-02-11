#ifndef ANCE_SRC_LANG_EXPRESSION_FUNCTIONCALL_H_
#define ANCE_SRC_LANG_EXPRESSION_FUNCTIONCALL_H_

#include "DelayableExpression.h"

#include <set>

#include "lang/construct/Function.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
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
    FunctionCall(lang::ResolvingHandle<lang::FunctionGroup> function_group,
                 std::vector<std::unique_ptr<Expression>>   arguments,
                 lang::Location                             location);

  protected:
    void setScope(lang::Scope* scope) override;

  public:
    lang::ResolvingHandle<lang::Type> type() override;

    bool validate(ValidationLogger& validation_logger) override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~FunctionCall() override;

  private:
    std::vector<lang::ResolvingHandle<lang::Function>> function();
    std::vector<lang::ResolvingHandle<lang::Type>>     argumentTypes();

    lang::ResolvingHandle<lang::FunctionGroup>         function_group_;
    std::vector<std::unique_ptr<Expression>>           arguments_;
    bool                                               overload_resolved_ {false};
    std::vector<lang::ResolvingHandle<lang::Function>> function_ {};
};

#endif