#ifndef ANCE_SRC_LANG_STATEMENT_STATEMENT_H_
#define ANCE_SRC_LANG_STATEMENT_STATEMENT_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/utility/Location.h"
#include "lang/Element.h"

namespace lang
{
    class Function;
    class Scope;
    class BasicBlock;
}

class CompileContext;
class ValidationLogger;

/**
 * Base class of all statements. Statements are building blocks of code and are ordered parts of functions.
 */
class Statement : public virtual lang::Visitable<ANCE_CONSTRUCTS>
{
  public:
    /**
     * Create a new statement.
     * @param location The source location.
     */
    explicit Statement(lang::Location location);

    /**
     * Create a basic block containing this statement.
     * @return The basic block.
     */
    virtual std::unique_ptr<lang::BasicBlock> createBlock();

    /**
     * Set the scope that contains this statement.
     * @param scope The containing scope.
     */
    void setContainingScope(lang::Scope* scope);

    /**
     * Get the containing scope.
     */
    [[nodiscard]] lang::Scope* scope() const;

    /**
     * Walk all definitions and declarations in this statement.
     * Use this for order-dependent definitions, as well as the usage of resolvable entities.
     */
    virtual void walkDefinitions() = 0;

  protected:
    /**
     * Override this to receive the containing function.
     * Order-dependent definitions should not happen here.
     * @param scope The containing function.
     */
    virtual void setScope(lang::Scope* scope);

  public:
    /**
     * Get the source location of this statement.
     */
    [[nodiscard]] lang::Location location() const;

    /**
     * Validate this statement.
     * @param validation_logger A logger to log validation messages.
     */
    virtual void validate(ValidationLogger& validation_logger) = 0;

    /**
     * Build this statement.
     * @param context The current compile context.
     */
    void build(CompileContext* context);

  protected:
    /**
     * Build this statement. Do not call this method, use build instead.
     * @param context The current compile context.
     */
    virtual void doBuild(CompileContext* context) = 0;

  public:
    ~Statement() override = default;

  private:
    lang::Location location_;

    lang::Scope* containing_scope_ = nullptr;
};

#endif