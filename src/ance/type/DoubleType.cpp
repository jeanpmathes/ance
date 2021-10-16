#include "DoubleType.h"

#include "ance/scope/GlobalScope.h"

ance::DoubleType::DoubleType() : Type("double") {}

llvm::Constant* ance::DoubleType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantFP::get(getContentType(c), 0);
}

llvm::Type* ance::DoubleType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getDoubleTy(c);
}

ance::FloatingPointType* ance::DoubleType::get()
{
    if (!instance_) { instance_ = new DoubleType(); }

    return instance_;
}
