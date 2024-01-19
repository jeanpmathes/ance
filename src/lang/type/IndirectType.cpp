#include "IndirectType.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "compiler/Runtime.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/value/Value.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/BooleanType.h"

lang::IndirectType::IndirectType(lang::ResolvingHandle<lang::Type> element_type) : value_type_(std::move(element_type))
{}

bool lang::IndirectType::definesIndirection() const
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::IndirectType::getIndirectionType()
{
    return value_type_;
}

bool lang::IndirectType::validateIndirection(lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::IndirectType::buildIndirection(Shared<lang::Value> value, CompileContext& context)
{
    auto value_reference = context.ctx().getReferenceType(value_type_);

    if (getIndirectionType()->getStateCount().isUnit()) return context.exec().getDefault(value_reference);

    if (context.ctx().isContainingRuntime())
    {
        Shared<lang::Value> not_null = context.exec().computeAddressIsNotNull(value);
        context.runtime().buildAssert(not_null, "Null pointer dereference at " + context.getLocationString(), context);
    }

    return context.exec().computeReferenceFromPointer(value);
}
