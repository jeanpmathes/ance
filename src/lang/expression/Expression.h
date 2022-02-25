#ifndef ANCE_SRC_LANG_EXPRESSION_EXPRESSION_H_
#define ANCE_SRC_LANG_EXPRESSION_EXPRESSION_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/type/Type.h"
#include "lang/utility/Location.h"
#include "lang/utility/ResolvingHandle.h"
#include "lang/Element.h"

namespace lang
{
    class Value;
    class Scope;
}

class CompileContext;
class ValidationLogger;

/**
 * The base class of all expressions.
 */
class Expression : public virtual lang::Visitable<ANCE_CONSTRUCTS>
{
  protected:
    /**
     * Create an expression.
     * @param location The source location of this expression. Use the zero location if the expression has no source location.
     */
    explicit Expression(lang::Location location);

  public:
    [[nodiscard]] lang::Location location() const;
    [[nodiscard]] lang::Scope*   scope() const;

    /**
     * Set the scope containing this expression.
     * @param scope The containing scope.
     */
    void setContainingScope(lang::Scope* scope);

    /**
     * Get whether this expression is a named value source.
     */
    [[nodiscard]] virtual bool isNamed();

    /**
     * Validate this expression.
     * @param validation_logger A logger to log validation messages.
     * @return Whether this expression is valid and dependent entities can be validated too.
     */
    virtual bool validate(ValidationLogger& validation_logger) = 0;

    /**
     * Validate an assignment to this expression.
     * @param value The value that would be assigned.
     * @param value_location The source location of the value.
     * @param validation_logger The validation logger to use.
     * @return True if assigning is valid.
     */
    virtual bool validateAssignment(const std::shared_ptr<lang::Value>& value,
                                    lang::Location                      value_location,
                                    ValidationLogger&                   validation_logger);

    /**
     * Build an assignment to this expression. The value should not be retrieved if assignment took place.
     * @param value The value to assign.
     * @param context The current compile context.
     */
    void assign(std::shared_ptr<lang::Value> value, CompileContext* context);

    /**
     * Get the return type of this expression.
     * @return The type of the value of this expression.
     */
    virtual lang::ResolvingHandle<lang::Type> type() = 0;
    /**
     * Get the value returned by this expression.
     * @return The value. One expression always returns the value.
     */
    [[nodiscard]] virtual std::shared_ptr<lang::Value> getValue() const = 0;

    virtual ~Expression() = default;

  protected:
    /**
     * Override this method to receive the containing scope.
     * @param scope The containing scope.
     */
    virtual void setScope(lang::Scope* scope);

    virtual void doAssign(std::shared_ptr<lang::Value> value, CompileContext* context);

  private:
    lang::Location location_;
    lang::Scope*   containing_scope_ {nullptr};
};

#endif