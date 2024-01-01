#include "DoubleType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/GlobalScope.h"

lang::DoubleType::DoubleType() : TypeDefinition(lang::Identifier::like("double")) {}

llvm::Constant* lang::DoubleType::getDefaultContent(CompileContext& context) const
{
    return llvm::ConstantFP::get(getContentType(context), 0);
}

llvm::Type* lang::DoubleType::getContentType(CompileContext& context) const
{
    return llvm::Type::getDoubleTy(context.exec().llvmContext());
}

size_t lang::DoubleType::getPrecision() const
{
    return 64;
}

lang::ResolvingHandle<lang::Type> lang::DoubleType::clone(lang::Context& new_context) const
{
    return new_context.getDoubleType();
}
