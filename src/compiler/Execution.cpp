#include "Execution.h"

#include "lang/construct/Constant.h"
#include "lang/type/Type.h"

Shared<lang::Value> Execution::performDereference(Shared<lang::Value> reference)
{
    return performLoadFromAddress(computePointerFromReference(reference));
}

Shared<lang::Value> Execution::performStackAllocation(lang::Type const& type)
{
    return performStackAllocation(type, getSizeN(1));
}
