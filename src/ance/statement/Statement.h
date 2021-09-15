#ifndef ANCE_SRC_ANCE_STATEMENT_STATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_STATEMENT_H_

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/utility/Location.h"
#include "compiler/CompileContext.h"
#include "validation/ValidationLogger.h"

class CompileContext;

namespace ance
{
    class DefinedFunction;
}

/**
 * Base class of all statements. Statements are building blocks of code and are ordered parts of functions.
 */
class Statement : public ance::Element
{
  public:
    /**
     * Create a new statement.
     * @param location The source location.
     */
    explicit Statement(ance::Location location);

    /**
     * Set the function that contains this statement.
     * @param function The containing function.
     */
    void setContainingFunction(ance::DefinedFunction* function);

  protected:
    /**
     * Override this to receive the containing function.
     * @param function The containing function.
     */
    virtual void setFunction(ance::DefinedFunction* function);

  public:
    /**
     * Get the function containing this statement.
     * @return The containing function.
     */
    [[nodiscard]] ance::DefinedFunction* getContainingFunction() const;

    [[nodiscard]] ance::Location location() const override;

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
    ance::Location location_;

    ance::DefinedFunction* function_ {nullptr};
};

#endif