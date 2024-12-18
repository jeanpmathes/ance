#ifndef ANCE_SRC_LANG_EXPRESSION_EXPRESSION_H_
#define ANCE_SRC_LANG_EXPRESSION_EXPRESSION_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/Element.h"
#include "lang/Located.h"
#include "lang/type/Type.h"
#include "lang/utility/Location.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Value;
    class Scope;
    class Context;
}

class Statement;
class Execution;
class ValidationLogger;

/**
 * The base class of all expressions.
 */
class Expression
    : public virtual lang::Visitable<ANCE_CONSTRUCTS>
    , public virtual lang::Located
{
  protected:
    /**
     * Create an expression.
     * @param location The source location of this expression. Use the zero location if the expression has no source location.
     */
    explicit Expression(lang::Location location);

  public:
    [[nodiscard]] lang::Location     location() const final;
    [[nodiscard]] lang::Scope&       scope() final;
    [[nodiscard]] lang::Scope const& scope() const final;

    [[nodiscard]] bool isInitialized() const;

    /**
     * Get the compile-time execution mode of this expression.
     * @return The compile-time execution mode.
     */
    [[nodiscard]] virtual lang::CMP cmp() const;

    /**
     * Set the scope containing this expression.
     * @param scope The containing scope.
     */
    void setContainingScope(lang::Scope& scope);

    /**
     * Walk all ordered definitions and declarations, as well as the usage of resolvable entities.
     */
    virtual void walkDefinitions();

    /**
     * Called after all entities have been resolved.
     */
    virtual void postResolve();

    /**
     * Get whether this expression is a named value source.
     */
    [[nodiscard]] virtual bool isNamed() const;

    /**
     * Validate this expression.
     * @param validation_logger A logger to log validation messages.
     * @return Whether this expression is valid and dependent entities can be validated too.
     */
    virtual bool validate(ValidationLogger& validation_logger) const = 0;

    /**
     * Validate an assignment to this expression.
     * @param value_type The type of the value to assign.
     * @param value_location The source location of the value.
     * @param validation_logger The validation logger to use.
     * @return True if assigning is valid.
     */
    virtual bool validateAssignment(lang::Type const& value_type,
                                    lang::Location    value_location,
                                    ValidationLogger& validation_logger) const;

    using Expansion = std::tuple<Statements, Owned<Expression>, Statements>;

    /**
     * Expand this expression to remove syntactic sugar.
     * @param new_context The context in which the expanded expression will be used.
     * @return The statements to use before and after the current containing statement, as well as a new expression.
     */
    [[nodiscard]] virtual Expansion expand(lang::Context& new_context) const;

    /**
     * Expand this expression with the given subexpressions.
     * @param subexpressions The subexpressions to use.
     * @return The statements to use before and after the current containing statement, as well as a new expression.
     */
    [[nodiscard]] virtual Expansion expandWith(Expressions subexpressions, lang::Context& new_context) const = 0;

    /**
     * Get the return type of this expression.
     * @return The type of the value of this expression. Might be undefined if the expression is not valid.
     */
    lang::ResolvingHandle<lang::Type> type();

    /**
     * Get the return type of this expression.
     * @return The type of the value of this expression. Might be undefined if the expression is not valid.
     */
    [[nodiscard]] lang::Type const& type() const;

    /**
     * The type of the assignable value of this expression.
     * Only valid to call if this expression is an assignable.
     * @return The type of the assignable value.
     */
    [[nodiscard]] virtual lang::Type const& assignableType() const;

    ~Expression() override = default;

  protected:
    /**
     * Define the type of this expression.
     * If this expression is valid, the type must be defined after a call to this method.
     * @param type The type to define. Should be rerouted to the return type of this expression.
     */
    virtual void defineType(lang::ResolvingHandle<lang::Type> type) = 0;

    /**
     * Override this method to receive the containing scope.
     * @param scope The containing scope.
     */
    virtual void setScope(lang::Scope& scope);

    /**
     * Add a subexpression to this expression.
     * @param subexpression The subexpression to add.
     */
    void addSubexpression(Expression& subexpression);

    /**
     * Get all return types of the given expressions.
     */
    static std::vector<lang::ResolvingHandle<lang::Type>> getTypes(std::vector<Owned<Expression>>& expressions);

    /**
     * Get all return types of the given expressions.
     */
    static std::vector<std::reference_wrapper<lang::Type const>> getTypes(
        std::vector<Owned<Expression>> const& expressions);

  protected:
    /**
     * Whether this expression, without considering subexpressions, can be evaluated at compile-time.
     * @return True if the root if the expression tree can be evaluated at compile-time.
     */
    [[nodiscard]] virtual lang::CMP rootCMP() const;

  private:
    lang::Location location_;
    lang::Scope*   containing_scope_ {nullptr};

    std::vector<std::reference_wrapper<Expression>> subexpressions_;

    lang::ResolvingHandle<lang::Type> type_;
};

#endif
