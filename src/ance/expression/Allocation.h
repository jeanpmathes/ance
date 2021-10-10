#ifndef ANCE_SRC_ANCE_EXPRESSION_ALLOCATION_H_
#define ANCE_SRC_ANCE_EXPRESSION_ALLOCATION_H_

#include "DelayableExpression.h"

#include "compiler/Runtime.h"

class Application;

/**
 * An allocation expression.
 */
class Allocation : public DelayableExpression
{
  public:
    /**
     * Create a new allocation.
     * @param allocation The allocation type.
     * @param type The type of the value to allocate.
     * @param count An expression providing the number of elements to allocate.
     * @param location The source location.
     */
    Allocation(Runtime::Allocator allocation,
               ance::Type*        type,
               Expression*        count,
               ance::Location     location);

  protected:
    void setScope(ance::Scope* scope) override;

  public:
    ance::Type* type() override;

    bool validate(ValidationLogger& validation_logger) override;

    bool accept(ance::ApplicationVisitor& visitor) override;

  protected:
    void doBuild(CompileContext* context) override;

  public:
    ~Allocation() override;

  private:
    Runtime::Allocator allocation_;
    ance::Type*        allocated_type_;
    Expression*        count_;
    ance::Type*        return_type_;
};

#endif
