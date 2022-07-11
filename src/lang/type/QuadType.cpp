#include "QuadType.h"

#include "lang/scope/GlobalScope.h"

lang::QuadType::QuadType() : TypeDefinition(lang::Identifier::from("quad")) {}

llvm::Constant* lang::QuadType::getDefaultContent(llvm::Module& m)
{
    return llvm::ConstantFP::get(getContentType(m.getContext()), 0);
}

llvm::Type* lang::QuadType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getFP128Ty(c);
}

size_t lang::QuadType::getPrecision() const
{
    return 128;
}

lang::ResolvingHandle<lang::Type> lang::QuadType::get()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new QuadType()));
    return instance;
}
