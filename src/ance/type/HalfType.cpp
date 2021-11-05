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

ance::Type* ance::HalfType::get()
{
    if (!instance_) { instance_ = new ance::Type(std::unique_ptr<ance::TypeDefinition>(new HalfType())); }

    return instance_;
}