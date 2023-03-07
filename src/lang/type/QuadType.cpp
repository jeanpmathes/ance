#include "QuadType.h"

#include "lang/ApplicationVisitor.h"
#include "lang/scope/GlobalScope.h"

lang::QuadType::QuadType() : TypeDefinition(lang::Identifier::like("quad")) {}

llvm::Constant* lang::QuadType::getDefaultContent(llvm::Module& m) const
{
    return llvm::ConstantFP::get(getContentType(m.getContext()), 0);
}

llvm::Type* lang::QuadType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::Type::getFP128Ty(c);
}

size_t lang::QuadType::getPrecision() const
{
    return 128;
}

lang::ResolvingHandle<lang::Type> lang::QuadType::clone(lang::Context& new_context) const
{
    return new_context.getQuadType();
}
