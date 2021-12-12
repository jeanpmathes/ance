#include "SingleType.h"

#include "ance/scope/GlobalScope.h"

ance::SingleType::SingleType() : TypeDefinition("single") {}

llvm::Constant* ance::SingleType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantFP::get(getContentType(c), 0);
}

llvm::Type* ance::SingleType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getFloatTy(c);
}

bool ance::SingleType::isFloatingPointType(size_t precision) const
{
    return precision == 32;
}

ance::ResolvingHandle<ance::Type> ance::SingleType::get()
{
    static ance::ResolvingHandle<ance::Type> instance =
        ance::makeHandled<ance::Type>(std::unique_ptr<ance::TypeDefinition>(new SingleType()));
    return instance;
}
