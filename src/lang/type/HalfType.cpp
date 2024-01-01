#include "HalfType.h"

#include "lang/scope/GlobalScope.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/type/Type.h"

lang::HalfType::HalfType() : TypeDefinition(lang::Identifier::like("half")) {}

llvm::Constant* lang::HalfType::getDefaultContent(CompileContext& context) const
{
    return llvm::ConstantFP::get(getContentType(context), 0);
}

llvm::Type* lang::HalfType::getContentType(CompileContext& context) const
{
    return llvm::Type::getHalfTy(context.exec().llvmContext());
}

size_t lang::HalfType::getPrecision() const
{
    return 16;
}

lang::ResolvingHandle<lang::Type> lang::HalfType::clone(lang::Context& new_context) const
{
    return new_context.getHalfType();
}
