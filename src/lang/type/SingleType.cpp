#include "SingleType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/GlobalScope.h"

lang::SingleType::SingleType() : TypeDefinition(lang::Identifier::like("single")) {}

llvm::Constant* lang::SingleType::getDefaultContent(CompileContext& context) const
{
    return llvm::ConstantFP::get(getContentType(context), 0);
}

llvm::Type* lang::SingleType::getContentType(CompileContext& context) const
{
    return llvm::Type::getFloatTy(context.exec().llvmContext());
}

size_t lang::SingleType::getPrecision() const
{
    return 32;
}

lang::ResolvingHandle<lang::Type> lang::SingleType::clone(lang::Context& new_context) const
{
    return new_context.getSingleType();
}
