#include "QuadType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/GlobalScope.h"

lang::QuadType::QuadType() : TypeDefinition(lang::Identifier::like("quad")) {}

llvm::Constant* lang::QuadType::getDefaultContent(CompileContext& context) const
{
    return llvm::ConstantFP::get(getContentType(context), 0);
}

llvm::Type* lang::QuadType::getContentType(CompileContext& context) const
{
    return llvm::Type::getFP128Ty(context.exec().llvmContext());
}

size_t lang::QuadType::getPrecision() const
{
    return 128;
}

lang::ResolvingHandle<lang::Type> lang::QuadType::clone(lang::Context& new_context) const
{
    return new_context.getQuadType();
}
