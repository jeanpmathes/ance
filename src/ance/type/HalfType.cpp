#include "HalfType.h"

#include <llvm/IR/Constants.h>

#include "GlobalScope.h"
#include "Scope.h"

std::string ance::HalfType::getName()
{
    return "half";
}

llvm::Constant* ance::HalfType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantFP::get(getNativeType(c), 0);
}

llvm::Type* ance::HalfType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getHalfTy(c);
}

ance::FloatingPointType* ance::HalfType::get()
{
    if (!instance_)
    {
        instance_ = new HalfType();
    }

    return instance_;
}