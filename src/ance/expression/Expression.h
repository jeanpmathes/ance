#ifndef ANCE_SRC_ANCE_EXPRESSION_EXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_EXPRESSION_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

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
class Expression
{
  public:
    /**
     * Set the scope containing this expression.
     * @param scope The containing scope.
     */
    virtual void setContainingScope(ance::Scope* scope);

    /**
     * Validate this expression.
     */
    virtual void validate() = 0;

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
};

#endif