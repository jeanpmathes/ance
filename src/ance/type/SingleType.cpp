#include "SingleType.h"

#include <llvm/IR/Constants.h>

#include "GlobalScope.h"
#include "Scope.h"

std::string ance::SingleType::getName()
{
    return "single";
}

llvm::Constant* ance::SingleType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantFP::get(getNativeType(c), 0);
}

llvm::Type* ance::SingleType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getFloatTy(c);
}

ance::FloatingPointType* ance::SingleType::get()
{
    if (!instance_)
    {
        instance_ = new SingleType();
    }

    return instance_;
}