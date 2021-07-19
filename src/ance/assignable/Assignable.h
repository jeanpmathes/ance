#ifndef ANCE_SRC_ANCE_ASSIGNABLE_ASSIGNABLE_H_
#define ANCE_SRC_ANCE_ASSIGNABLE_ASSIGNABLE_H_

#include "ance/scope/Scope.h"
#include "ance/construct/value/Value.h"

class Assignable
{
  public:
    virtual void setScope(ance::Scope* scope) = 0;
    virtual void assign(ance::Value* value, CompileContext* context) = 0;

    virtual ~Assignable() = default;
};

#endif
