#include "SingleType.h"

#include "lang/scope/GlobalScope.h"

lang::SingleType::SingleType() : TypeDefinition(lang::Identifier::from("single")) {}

llvm::Constant* lang::SingleType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantFP::get(getContentType(c), 0);
}

llvm::Type* lang::SingleType::getContentType(llvm::LLVMContext& c)
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
