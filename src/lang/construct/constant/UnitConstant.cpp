#include "UnitConstant.h"

#include "compiler/Execution.h"
#include "lang/ApplicationVisitor.h"
#include "lang/Context.h"

lang::UnitConstant::UnitConstant(lang::Context& context) : LiteralConstant(context.getUnitType()) {}

std::string lang::UnitConstant::toString() const
{
    return "()";
}

Shared<lang::Constant> lang::UnitConstant::embed(Execution& exec) const
{
    return exec.getDefault(type());
}

bool lang::UnitConstant::equals(lang::Constant const* other) const
{
    auto* other_null = dynamic_cast<UnitConstant const*>(other);
    return other_null != nullptr;
}

Shared<lang::LiteralConstant> lang::UnitConstant::clone(lang::Context& new_context) const
{
    return makeShared<lang::UnitConstant>(new_context);
}
