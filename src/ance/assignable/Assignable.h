#ifndef ANCE_SRC_ANCE_ASSIGNABLE_ASSIGNABLE_H_
#define ANCE_SRC_ANCE_ASSIGNABLE_ASSIGNABLE_H_

#include "ance/construct/value/Value.h"
#include "ance/scope/Scope.h"

/**
 * Represents a construct that values can be assigned to.
 */
class Assignable
{
  protected:
    explicit Assignable(ance::Location location);

  public:
    /**
     * Set the containing scope of this assignable.
     * @param scope The containing scope.
     */
    void setContainingScope(ance::Scope* scope);
    /**
     * Build a value assignment to this assignable.
     * @param value The value that should be assigned.
     * @param context The compile context.
     */
    void assign(ance::Value* value, CompileContext* context);

  protected:
    /**
     * Override to receive the containing scope.
     * @param scope The containing scope.
     */
    virtual void setScope(ance::Scope* scope) = 0;

    /**
     * Build an assignment to this assignable.
     * @param value The value to assign.
     * @param context The current compile context.
     */
    virtual void buildAssignment(ance::Value* value, CompileContext* context) = 0;

  public:
    virtual ~Assignable() = default;

  private:
    ance::Location location_;
    ance::Scope*   containing_scope_ {nullptr};
};

#endif
