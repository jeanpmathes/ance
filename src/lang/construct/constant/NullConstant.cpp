#include "NullConstant.h"

#include "compiler/Execution.h"
#include "lang/ApplicationVisitor.h"
#include "lang/Context.h"
#include "lang/type/NullValueType.h"

lang::NullConstant::NullConstant(lang::Context& new_context) : LiteralConstant(new_context.getNullValueType()) {}

std::string lang::NullConstant::toString() const
{
    return "null";
}

Shared<lang::Constant> lang::NullConstant::embed(Execution& exec) const
{
    return exec.getDefault(type());
}

bool lang::NullConstant::equals(lang::Constant const* other) const
{
    auto* other_null = dynamic_cast<NullConstant const*>(other);
    return other_null != nullptr;
}

Shared<lang::LiteralConstant> lang::NullConstant::clone(lang::Context& new_context) const
{
    return create(new_context);
}

Shared<lang::NullConstant> lang::NullConstant::create(lang::Context& new_context)
{
    return makeShared<lang::NullConstant>(new_context);
}
