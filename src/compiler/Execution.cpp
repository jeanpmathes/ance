#include "Execution.h"

#include "compiler/Runtime.h"
#include "compiler/Unit.h"
#include "lang/construct/Constant.h"
#include "lang/construct/descriptions/Description.h"
#include "lang/type/Type.h"
#include "lang/type/VectorType.h"

Execution::Execution(Unit& unit, Runtime& runtime) : unit_(unit), runtime_(runtime) {}

Shared<lang::Constant> Execution::getZero(lang::Type const& type)
{
    return getN(static_cast<uint64_t>(0), type);
}

Shared<lang::Constant> Execution::getOne(lang::Type const& type)
{
    return getN(static_cast<uint64_t>(1), type);
}

Shared<lang::Constant> Execution::getByte(uint8_t byte)
{
    llvm::APInt value(8, static_cast<uint64_t>(byte), false);
    return getInteger(value, ctx().getFixedWidthIntegerType(8, false));
}

Shared<lang::Constant> Execution::getSplatVector(Shared<lang::Constant> value, lang::Type const& type)
{
    size_t size = type.isVectorType()->getSize().value();

    std::vector<Shared<lang::Constant>> values;
    values.reserve(size);

    for (uint64_t index = 0; index < size; index++) { values.emplace_back(value); }

    return getVector(std::move(values), type);
}

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
