#include "SingleType.h"

#include "ance/scope/GlobalScope.h"
#include "ance/type/Type.h"

ance::SingleType::SingleType() : TypeDefinition("single") {}

llvm::Constant* ance::SingleType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantFP::get(getContentType(c), 0);
}

llvm::Type* ance::SingleType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getFloatTy(c);
}

ance::Type* ance::SingleType::get()
{
    if (!instance_) { instance_ = new ance::Type(std::unique_ptr<ance::TypeDefinition>(new SingleType())); }

    return instance_;
}