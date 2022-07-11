#include "HalfType.h"

#include "lang/scope/GlobalScope.h"

#include "lang/type/Type.h"

lang::HalfType::HalfType() : TypeDefinition(lang::Identifier::from("half")) {}

llvm::Constant* lang::HalfType::getDefaultContent(llvm::Module& m)
{
    return llvm::ConstantFP::get(getContentType(m.getContext()), 0);
}

llvm::Type* lang::HalfType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getHalfTy(c);
}

size_t lang::HalfType::getPrecision() const
{
    return 16;
}

lang::ResolvingHandle<lang::Type> lang::HalfType::get()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new HalfType()));
    return instance;
}
