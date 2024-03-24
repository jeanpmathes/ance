#include "Execution.h"

#include "compiler/Runtime.h"
#include "compiler/Unit.h"
#include "lang/construct/Constant.h"
#include "lang/construct/descriptions/Description.h"
#include "lang/type/Type.h"

Execution::Execution(Unit& unit, Runtime& runtime) : unit_(unit), runtime_(runtime) {}

Shared<lang::Value> Execution::performDereference(Shared<lang::Value> reference)
{
    return performLoadFromAddress(computePointerFromReference(reference));
}

Shared<lang::Value> Execution::performStackAllocation(lang::Type const& type)
{
    return performStackAllocation(type, getSizeN(1));
}

Unit& Execution::unit()
{
    return unit_;
}

Runtime& Execution::runtime()
{
    return runtime_;
}

lang::Context& Execution::ctx()
{
    return unit_.globalScope().context();
}
