#include "QuadType.h"

#include "ance/scope/GlobalScope.h"

std::string ance::QuadType::getName()
{
    return "quad";
}

llvm::Constant* ance::QuadType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantFP::get(getContentType(c), 0);
}

llvm::Type* ance::QuadType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getFP128Ty(c);
}

ance::FloatingPointType* ance::QuadType::get()
{
    if (!instance_) { instance_ = new QuadType(); }

    return instance_;
}