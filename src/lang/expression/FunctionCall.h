#ifndef ANCE_SRC_LANG_EXPRESSION_FUNCTIONCALL_H_
#define ANCE_SRC_LANG_EXPRESSION_FUNCTIONCALL_H_

#include "DelayableExpression.h"

#include <set>

#include "lang/construct/Function.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/Element.h"

namespace lang
{
    class Scope;
}

/**
 * A call to a function.
 */
class FunctionCall
    : public DelayableExpression
    , public lang::Element<FunctionCall, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new function call.
     * @param function_group The function group to call, if there is any.
     * @param type_function_group A type to be used instead of the function group, if necessary.
     * @param arguments The arguments to pass to the called function.
     * @param location The source location.
     */
    FunctionCall(std::optional<lang::ResolvingHandle<lang::FunctionGroup>> function_group,
                 lang::ResolvingHandle<lang::Type>                         type_function_group,
                 std::vector<std::unique_ptr<Expression>>                  arguments,
                 lang::Location                                            location);

    [[nodiscard]] const lang::Callable&                           callable() const;
    [[nodiscard]] std::vector<std::reference_wrapper<Expression>> arguments() const;

  private:
    lang::Callable& getCallable();

  protected:
    void walkDefinitions() override;
    void postResolve() override;

  public:
    [[nodiscard]] std::optional<lang::ResolvingHandle<lang::Type>> tryGetType() const override;

    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions) const override;

  protected:
    void doBuild(CompileContext& context) override;

  public:
    ~FunctionCall() override;

  private:
    std::vector<lang::ResolvingHandle<lang::Function>> function() const;
    std::vector<lang::ResolvingHandle<lang::Type>>                argumentTypes() const;
    std::vector<std::optional<lang::ResolvingHandle<lang::Type>>> tryArgumentTypes() const;

    std::optional<lang::ResolvingHandle<lang::FunctionGroup>> function_group_;
    lang::ResolvingHandle<lang::Type>                         type_function_group_;
    std::vector<std::unique_ptr<Expression>>                  arguments_;

    mutable const lang::Callable*                              used_callable_ {};
    mutable bool                                               overload_resolved_ {false};
    mutable std::vector<lang::ResolvingHandle<lang::Function>> function_ {};
};

#endif
