#ifndef ANCE_SRC_LANG_EXPRESSION_FUNCTIONCALL_H_
#define ANCE_SRC_LANG_EXPRESSION_FUNCTIONCALL_H_

#include "DelayableExpression.h"

#include <set>

#include "lang/Element.h"
#include "lang/construct/Function.h"
#include "lang/utility/ResolvingHandle.h"

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
    FunctionCall(Optional<lang::ResolvingHandle<lang::FunctionGroup>> function_group,
                 lang::ResolvingHandle<lang::Type>                    type_function_group,
                 std::vector<Owned<Expression>>                       arguments,
                 lang::Location                                       location);

    [[nodiscard]] lang::Callable const&                                 callable() const;
    [[nodiscard]] std::vector<std::reference_wrapper<Expression const>> arguments() const;

  private:
    lang::Callable& getCallable();

  protected:
    void walkDefinitions() override;
    void postResolve() override;

  public:
    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;
    void doBuild(CompileContext& context) override;

  public:
    ~FunctionCall() override;

  private:
    std::vector<lang::ResolvingHandle<lang::Function>>    function();
    std::vector<std::reference_wrapper<lang::Type const>> argumentTypes() const;

    Optional<lang::ResolvingHandle<lang::FunctionGroup>> function_group_;
    lang::ResolvingHandle<lang::Type>                    type_function_group_;
    std::vector<Owned<Expression>>                       arguments_;

    mutable lang::Callable const*                              used_callable_ {};
    mutable bool                                               overload_resolved_ {false};
    mutable std::vector<lang::ResolvingHandle<lang::Function>> function_ {};

  private:
    template<typename, typename>
    friend struct GetCallable;
};

#endif
