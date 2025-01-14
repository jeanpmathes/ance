#include "SingleType.h"

#include "lang/ApplicationVisitor.h"
#include "lang/scope/GlobalScope.h"

lang::SingleType::SingleType() : TypeDefinition(lang::Identifier::like("single")) {}

size_t lang::SingleType::getPrecision() const
{
    return 32;
}

lang::ResolvingHandle<lang::Type> lang::SingleType::clone(lang::Context& new_context) const
{
    return new_context.getSingleType();
}
