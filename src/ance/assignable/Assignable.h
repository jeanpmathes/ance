#ifndef ANCE_SRC_ANCE_ASSIGNABLE_ASSIGNABLE_H_
#define ANCE_SRC_ANCE_ASSIGNABLE_ASSIGNABLE_H_

#include "ance/construct/value/Value.h"
#include "ance/scope/Scope.h"

/**
 * Represents a construct that values can be assigned to.
 */
class Assignable
{
  public:
    /**
     * Set the containing scope of this assignable.
     * @param scope The containing scope.
     */
    virtual void setScope(ance::Scope* scope) = 0;
    /**
     * Build a value assignment to this assignable.
     * @param value The value that should be assigned.
     * @param context The compile context.
     */
    virtual void assign(ance::Value* value, CompileContext* context) = 0;

    virtual ~Assignable() = default;
};

#endif
