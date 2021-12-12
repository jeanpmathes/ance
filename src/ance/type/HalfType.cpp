#include "HalfType.h"

#include "ance/scope/GlobalScope.h"

#include "ance/type/Type.h"

ance::HalfType::HalfType() : TypeDefinition("half") {}

llvm::Constant* ance::HalfType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantFP::get(getContentType(c), 0);
}

llvm::Type* ance::HalfType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getHalfTy(c);
}

bool ance::HalfType::isFloatingPointType(size_t precision) const
{
    return precision == 16;
}

ance::ResolvingHandle<ance::Type> ance::HalfType::get()
{
    static ance::ResolvingHandle<ance::Type> instance =
        ance::makeHandled<ance::Type>(std::unique_ptr<ance::TypeDefinition>(new HalfType()));
    return instance;
}
