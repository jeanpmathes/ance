#ifndef ANCE_SRC_ANCE_EXPRESSION_EXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_EXPRESSION_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/Element.h"
#include "validation/ValidationLogger.h"

class CompileContext;

namespace ance
{
    class Value;
    class Type;
    class Scope;
}

/**
 * The base class of all expressions.
 */
class Expression : public ance::Element
{
  protected:
    /**
     * Create an expression.
     * @param location The source location of this expression. Use the zero location if the expression has no source location.
     */
    explicit Expression(ance::Location location);

  public:
    /**
     * Get the source location.
     * @return The source location. Might not refer to an actual location.
     */
    [[nodiscard]] ance::Location location() const;

    /**
     * Set the scope containing this expression.
     * @param scope The containing scope.
     */
    virtual void setContainingScope(ance::Scope* scope);

    /**
     * Validate this expression.
     * @param validation_logger A logger to log validation messages.
     * @return Whether this expression is valid and dependent entities can be validated too.
     */
    virtual bool validate(ValidationLogger& validation_logger) = 0;

    /**
     * Get the return type of this expression.
     * @return The type of the value of this expression.
     */
    virtual ance::Type* type() = 0;
    /**
     * Get the value returned by this expression.
     * @return The value. One expression always returns the value.
     */
    [[nodiscard]] virtual ance::Value* getValue() const = 0;

    virtual ~Expression() = default;

  private:
    ance::Location location_;
};

#endif