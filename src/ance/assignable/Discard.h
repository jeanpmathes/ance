#ifndef ANCE_SRC_ANCE_ASSIGNABLE_DISCARD_H_
#define ANCE_SRC_ANCE_ASSIGNABLE_DISCARD_H_

#include "Assignable.h"

class Discard : public Assignable
{
  public:
    void setScope(ance::Scope* scope) override;

    void assign(ance::Value* value, CompileContext* context) override;
};

#endif
