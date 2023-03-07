#include "DoubleType.h"

#include "lang/ApplicationVisitor.h"
#include "lang/scope/GlobalScope.h"

lang::DoubleType::DoubleType() : TypeDefinition(lang::Identifier::like("double")) {}

llvm::Constant* lang::DoubleType::getDefaultContent(llvm::Module& m) const
{
    return llvm::ConstantFP::get(getContentType(m.getContext()), 0);
}

llvm::Type* lang::DoubleType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::Type::getDoubleTy(c);
}

size_t lang::DoubleType::getPrecision() const
{
    return 64;
}

lang::ResolvingHandle<lang::Type> lang::DoubleType::clone(lang::Context& new_context) const
{
    return new_context.getDoubleType();
}
