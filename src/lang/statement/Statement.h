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

class Expression;
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
     * Create the basis blocks that make up this statement.
     * @param entry The entry block.
     * @param function The function this statement is part of.
     * @return The basic blocks.
     */
    virtual std::vector<std::unique_ptr<lang::BasicBlock>> createBasicBlocks(lang::BasicBlock& entry,
                                                                             lang::Function&   function);

    /**
     * Set the scope that contains this statement.
     * @param scope The containing scope.
     */
    void setContainingScope(lang::Scope& scope);

    /**
     * Get the containing scope.
     */
    [[nodiscard]] lang::Scope* scope() const;

    /**
     * Get the block scope of the statement, if any.
     * For compound statements the block scope is the scope that contains all the statements.
     * @return The block scope, or nullptr.
     */
    [[nodiscard]] virtual lang::LocalScope* getBlockScope() const;

    /**
     * Get whether this statement is a compound statement.
     * A compound statement has it's own scope and can contain multiple statements.
     * @return True if this statement is a compound statement.
     */
    [[nodiscard]] virtual bool isCompound() const;

    /**
     * Walk all definitions and declarations in this statement.
     * Use this for order-dependent definitions, as well as the usage of resolvable entities.
     */
    virtual void walkDefinitions();

  protected:
    /**
     * Override this to receive the containing function.
     * Order-dependent definitions should not happen here.
     * @param scope The containing function.
     */
    virtual void setScope(lang::Scope& scope);

  public:
    /**
     * Get the source location of this statement.
     */
    [[nodiscard]] lang::Location location() const;

    /**
     * Validate this statement.
     * @param validation_logger A logger to log validation messages.
     */
    virtual void validate(ValidationLogger& validation_logger) const = 0;

    /**
     * Expand this statement into new statements that do not use syntactic sugar.
     * @return The expanded statements.
     */
    [[nodiscard]] virtual Statements expand() const;

    /**
     * Expand this statement into new statements with the given sub-elements.
     * @param subexpressions The subexpressions to use.
     * @param substatements The substatements to use.
     * @return The expanded statements.
     */
    [[nodiscard]] virtual Statements expandWith(Expressions subexpressions, Statements substatements) const = 0;

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

    /**
     * Add a subexpression to the current statement.
     * @param subexpression The subexpression to add.
     */
    void addSubexpression(Expression& subexpression);

    /**
     * Add a substatement to the current statement.
     * @param substatement The substatement to add.
     */
    void addSubstatement(Statement& substatement);

  public:
    ~Statement() override = default;

  private:
    lang::Location location_;

    lang::Scope* containing_scope_ = nullptr;

    std::vector<std::reference_wrapper<Expression>> subexpressions_;
    std::vector<std::reference_wrapper<Statement>>  substatements_;
};

#endif