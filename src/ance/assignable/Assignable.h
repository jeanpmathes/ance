#ifndef ANCE_SRC_ANCE_ASSIGNABLE_ASSIGNABLE_H_
#define ANCE_SRC_ANCE_ASSIGNABLE_ASSIGNABLE_H_

#include "ance/Element.h"
#include "ance/construct/value/Value.h"
#include "ance/scope/Scope.h"
#include "validation/ValidationLogger.h"

/**
 * Represents a construct that values can be assigned to.
 */
class Assignable : public ance::Element
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
     * @param location The source location
     */
    void assign(ance::Value* value, ance::Location location);

    /**
     * Validate this assignable.
     * @param validation_logger A logger to log validation messages.
     */
    virtual void validate(ValidationLogger& validation_logger) = 0;

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
    [[nodiscard]] ance::Value* assigned() const;

    /**
     * Get the location of the assigned value.
     * @return The assigned value source location.
     */
    [[nodiscard]] ance::Location assignedLocation() const;

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

    /**
     * Get the location of this assignable.
     * @return The source location.
     */
    [[nodiscard]] ance::Location location() const;

  public:
    virtual ~Assignable() = default;

  private:
    ance::Location location_;
    ance::Scope*   containing_scope_ {nullptr};

    ance::Value*   assigned_value_ {nullptr};
    ance::Location assigned_location_ {ance::Location(0, 0, 0, 0)};
};

#endif
