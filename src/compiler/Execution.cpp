#include "Execution.h"

Shared<lang::Value> Execution::performDereference(Shared<lang::Value> reference)
{
    return performLoadFromAddress(computePointerFromReference(reference));
}

Shared<lang::Value> Execution::performStackAllocation(lang::ResolvingHandle<lang::Type> type)
{
    return performStackAllocation(type, getSizeValue(1));
}
