#include "SingleType.h"

#include "lang/ApplicationVisitor.h"
#include "lang/scope/GlobalScope.h"

lang::SingleType::SingleType() : TypeDefinition(lang::Identifier::from("single")) {}

llvm::Constant* lang::SingleType::getDefaultContent(llvm::Module& m)
{
    return llvm::ConstantFP::get(getContentType(m.getContext()), 0);
}

llvm::Type* lang::SingleType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::Type::getFloatTy(c);
}

size_t lang::SingleType::getPrecision() const
{
    return 32;
}

lang::ResolvingHandle<lang::Type> lang::SingleType::get()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new SingleType()));
    return instance;
}

