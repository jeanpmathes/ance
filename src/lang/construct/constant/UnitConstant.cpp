#include "UnitConstant.h"

#include "compiler/CompileContext.h"
#include "compiler/Execution.h"
#include "lang/ApplicationVisitor.h"
#include "lang/Context.h"

lang::UnitConstant::UnitConstant(lang::Context& new_context) : type_(new_context.getUnitType()) {}

std::string lang::UnitConstant::toString() const
{
    return "()";
}

lang::ResolvingHandle<lang::Type> lang::UnitConstant::type()
{
    return type_;
}

lang::Type const& lang::UnitConstant::type() const
{
    return type_;
}

Shared<lang::Constant> lang::UnitConstant::createContent(CompileContext& context)
{
    return context.exec().getDefault(type_);
}

bool lang::UnitConstant::equals(lang::Constant const* other) const
{
    auto* other_null = dynamic_cast<UnitConstant const*>(other);
    return other_null != nullptr;
}

Shared<lang::Constant> lang::UnitConstant::clone(lang::Context& new_context) const
{
    return create(new_context);
}

Shared<lang::UnitConstant> lang::UnitConstant::create(lang::Context& new_context)
{
    return makeShared<lang::UnitConstant>(new_context);
}
