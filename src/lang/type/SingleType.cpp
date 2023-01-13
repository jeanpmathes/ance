#include "SingleType.h"

#include "lang/ApplicationVisitor.h"
#include "lang/scope/GlobalScope.h"

lang::SingleType::SingleType() : TypeDefinition(lang::Identifier::like("single")) {}

llvm::Constant* lang::SingleType::getDefaultContent(llvm::Module& m) const
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
#define MAKE lang::makeHandled<lang::Type>(Owned<lang::TypeDefinition>(*(new SingleType())))

    static lang::ResolvingHandle<lang::Type> instance = MAKE;

    if (!instance.valid()) instance = MAKE;

    return instance;
#undef MAKE
}

lang::ResolvingHandle<lang::Type> lang::SingleType::clone() const
{
    return get();
}
