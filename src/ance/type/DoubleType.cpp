#include "DoubleType.h"

#include "ance/scope/GlobalScope.h"

ance::DoubleType::DoubleType() : TypeDefinition("double") {}

llvm::Constant* ance::DoubleType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantFP::get(getContentType(c), 0);
}

llvm::Type* ance::DoubleType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getDoubleTy(c);
}

ance::ResolvingHandle<ance::Type> ance::DoubleType::get()
{
    static ance::ResolvingHandle<ance::Type> instance =
        ance::makeHandled<ance::Type>(std::unique_ptr<ance::TypeDefinition>(new DoubleType()));
    return instance;
}
