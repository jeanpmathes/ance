#ifndef ANCE_SRC_LANG_EXPRESSION_FUNCTIONCALL_H_
#define ANCE_SRC_LANG_EXPRESSION_FUNCTIONCALL_H_

#include "CompileTimeExpression.h"

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
    : public CompileTimeExpression
    , public lang::Element<FunctionCall, ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new function call.
     * @param callable The callable to call.
     * @param arguments The arguments to pass to the called function.
     * @param location The source location.
     */
    FunctionCall(lang::ResolvingHandle<lang::Entity> callable,
                 std::vector<Owned<Expression>>      arguments,
                 lang::Location                      location);

    [[nodiscard]] lang::Entity const&                                   callee() const;
    [[nodiscard]] std::vector<std::reference_wrapper<Expression const>> arguments() const;

    [[nodiscard]] lang::Function const& function() const;

  private:
    [[nodiscard]] lang::Callable const* getCallable() const;
    lang::Callable*                     getCallable();

  protected:
    void walkDefinitions() override;
    void postResolve() override;

    bool isRootCMP() const override;

  public:
    bool validate(ValidationLogger& validation_logger) const override;

    [[nodiscard]] Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const override;

  protected:
    void defineType(lang::ResolvingHandle<lang::Type> type) override;

  public:
    ~FunctionCall() override;

  private:
    std::vector<lang::ResolvingHandle<lang::Function>>    function();
    std::vector<std::reference_wrapper<lang::Type const>> argumentTypes() const;

    lang::ResolvingHandle<lang::Entity> callable_;
    std::vector<Owned<Expression>>      arguments_;

    mutable Optional<lang::Callable const*>                    used_callable_ {};
    mutable bool                                               overload_resolved_ {false};
    mutable std::vector<lang::ResolvingHandle<lang::Function>> function_ {};

  private:
    template<typename, typename>
    friend struct GetCallable;
};

#endif
