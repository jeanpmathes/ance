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
     * Assign a value to this assignable.
     * @param value The value to assign.
     */
    void assign(ance::Value* value);

    /**
     * Validate this assignable.
     */
    virtual void validate() = 0;

    /**
     * Build this assignable and the contained assignment.
     * @param context The current compile context.
     */
    void build(CompileContext* context);

  protected:
    /**
     * Get the assigned value.
     * @return The assigned value.
     */
    ance::Value* assigned();

    /**
     * Override to receive the containing scope.
     * @param scope The containing scope.
     */
    virtual void setScope(ance::Scope* scope) = 0;

    /**
     * Build the assignment of this assignable.
     * @param context The current compile context.
     */
    virtual void doBuild(CompileContext* context) = 0;

  public:
    virtual ~Assignable() = default;

  private:
    ance::Location location_;
    ance::Scope*   containing_scope_ {nullptr};
    ance::Value*   assigned_value_ {nullptr};
};

#endif
