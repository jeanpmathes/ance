#ifndef ANCE_SRC_ANCE_ASSIGNABLE_DISCARD_H_
#define ANCE_SRC_ANCE_ASSIGNABLE_DISCARD_H_

#include "Assignable.h"

/**
 * An assignable that does nothing with the assigned value.
 */
class Discard : public Assignable
{
  public:
    /**
     * Create a new discard assignable.
     * @param location The source location.
     */
    explicit Discard(ance::Location location);

    void validate() override;

  protected:
    void setScope(ance::Scope* scope) override;
    void doBuild(CompileContext* context) override;
};

#endif
