#include "HalfType.h"

#include "lang/scope/GlobalScope.h"

#include "lang/ApplicationVisitor.h"
#include "lang/type/Type.h"

lang::HalfType::HalfType() : TypeDefinition(lang::Identifier::like("half")) {}

size_t lang::HalfType::getPrecision() const
{
    return 16;
}

lang::ResolvingHandle<lang::Type> lang::HalfType::clone(lang::Context& new_context) const
{
    return new_context.getHalfType();
}
