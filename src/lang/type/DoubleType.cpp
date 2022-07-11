#include "DoubleType.h"

#include "lang/scope/GlobalScope.h"

lang::DoubleType::DoubleType() : TypeDefinition(lang::Identifier::from("double")) {}

llvm::Constant* lang::DoubleType::getDefaultContent(llvm::Module& m)
{
    return llvm::ConstantFP::get(getContentType(m.getContext()), 0);
}

llvm::Type* lang::DoubleType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getDoubleTy(c);
}

size_t lang::DoubleType::getPrecision() const
{
    return 64;
}

lang::ResolvingHandle<lang::Type> lang::DoubleType::get()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new DoubleType()));
    return instance;
}
