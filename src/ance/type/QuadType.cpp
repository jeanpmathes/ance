#include "QuadType.h"

#include "ance/scope/GlobalScope.h"
#include "ance/type/Type.h"

ance::QuadType::QuadType() : TypeDefinition("quad") {}

llvm::Constant* ance::QuadType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantFP::get(getContentType(c), 0);
}

llvm::Type* ance::QuadType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getFP128Ty(c);
}

ance::Type* ance::QuadType::get()
{
    if (!instance_) { instance_ = new ance::Type(std::unique_ptr<ance::TypeDefinition>(new QuadType())); }

    return instance_;
}