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

lang::ResolvingHandle<lang::Type> lang::DoubleType::get()
{
#define MAKE lang::makeHandled<lang::Type>(Owned<lang::TypeDefinition>(*(new DoubleType())))

    static lang::ResolvingHandle<lang::Type> instance = MAKE;

    if (!instance.valid()) instance = MAKE;

    return instance;
#undef MAKE
}

lang::ResolvingHandle<lang::Type> lang::DoubleType::clone() const
{
    return get();
}
