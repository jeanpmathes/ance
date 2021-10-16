#include "SingleType.h"

#include "ance/scope/GlobalScope.h"

ance::SingleType::SingleType() : Type("single") {}

llvm::Constant* ance::SingleType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantFP::get(getContentType(c), 0);
}

llvm::Type* ance::SingleType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getFloatTy(c);
}

ance::FloatingPointType* ance::SingleType::get()
{
    if (!instance_) { instance_ = new SingleType(); }

    return instance_;
}