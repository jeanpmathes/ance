#include "QuadType.h"

#include "ance/scope/GlobalScope.h"

ance::QuadType::QuadType() : TypeDefinition("quad") {}

llvm::Constant* ance::QuadType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantFP::get(getContentType(c), 0);
}

llvm::Type* ance::QuadType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getFP128Ty(c);
}

size_t ance::QuadType::getPrecision() const
{
    return 128;
}

ance::ResolvingHandle<ance::Type> ance::QuadType::get()
{
    static ance::ResolvingHandle<ance::Type> instance =
        ance::makeHandled<ance::Type>(std::unique_ptr<ance::TypeDefinition>(new QuadType()));
    return instance;
}
