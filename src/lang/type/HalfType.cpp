#include "HalfType.h"

#include "lang/scope/GlobalScope.h"

#include "lang/ApplicationVisitor.h"
#include "lang/type/Type.h"

lang::HalfType::HalfType() : TypeDefinition(lang::Identifier::like("half")) {}

llvm::Constant* lang::HalfType::getDefaultContent(llvm::Module& m) const
{
    return llvm::ConstantFP::get(getContentType(m.getContext()), 0);
}

llvm::Type* lang::HalfType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::Type::getHalfTy(c);
}

size_t lang::HalfType::getPrecision() const
{
    return 16;
}

lang::ResolvingHandle<lang::Type> lang::HalfType::get()
{
#define MAKE lang::makeHandled<lang::Type>(Owned<lang::TypeDefinition>(*(new HalfType())))

    static lang::ResolvingHandle<lang::Type> instance = MAKE;

    if (not instance.valid()) instance = MAKE;

    return instance;
#undef MAKE
}

lang::ResolvingHandle<lang::Type> lang::HalfType::clone() const
{
    return get();
}
