#include "IndirectType.h"

#include <utility>

#include "compiler/Runtime.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Value.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/BooleanType.h"

lang::IndirectType::IndirectType(lang::ResolvingHandle<lang::Type> element_type) : value_type_(std::move(element_type))
{}

bool lang::IndirectType::definesIndirection() const
{
    return true;
}

lang::Type const& lang::IndirectType::getIndirectionType() const
{
    return value_type_;
}

bool lang::IndirectType::validateIndirection(lang::Location, ValidationLogger&) const
{
    return true;
}

Shared<lang::Value> lang::IndirectType::execIndirection(Shared<lang::Value> value, Execution& exec) const
{
    auto const& value_reference = exec.ctx().getReferenceType(*value_type_);

    if (getIndirectionType().getStateCount().isUnit()) return exec.getDefault(value_reference);

    if (exec.ctx().isContainingRuntime())
    {
        Shared<lang::Value> not_null = exec.computeAddressIsNotNull(value);
        exec.runtime().execAssert(not_null, "Null pointer dereference at " + exec.getLocationString(), exec);
    }

    return exec.computeReferenceFromPointer(value);
}
