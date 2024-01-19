#include "QuadType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/GlobalScope.h"

lang::QuadType::QuadType() : TypeDefinition(lang::Identifier::like("quad")) {}

size_t lang::QuadType::getPrecision() const
{
    return 128;
}

lang::ResolvingHandle<lang::Type> lang::QuadType::clone(lang::Context& new_context) const
{
    return new_context.getQuadType();
}
