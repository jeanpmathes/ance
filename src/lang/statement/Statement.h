#ifndef ANCE_SRC_LANG_STATEMENT_STATEMENT_H_
#define ANCE_SRC_LANG_STATEMENT_STATEMENT_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/utility/Location.h"

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
class Statement
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
     * Set the function that contains this statement.
     * @param function The containing function.
     */
    void setContainingFunction(lang::Function* function);

    /**
     * Get the containing scope.
     */
    [[nodiscard]] lang::Scope* scope() const;

  protected:
    /**
     * Override this to receive the containing function.
     * @param function The containing function.
     */
    virtual void setFunction(lang::Function* function);

  public:
    /**
     * Get the function containing this statement.
     * @return The containing function.
     */
    [[nodiscard]] lang::Function* getContainingFunction() const;

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
    virtual ~Statement() = default;

  private:
    lang::Location location_;

    lang::Function* function_ {nullptr};
};

#endif