#include "DoubleType.h"

#include "ance/scope/GlobalScope.h"
#include "ance/type/Type.h"

ance::DoubleType::DoubleType() : TypeDefinition("double") {}

llvm::Constant* ance::DoubleType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantFP::get(getContentType(c), 0);
}

llvm::Type* ance::DoubleType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getDoubleTy(c);
}

ance::Type* ance::DoubleType::get()
{
    if (!instance_) { instance_ = new ance::Type(std::unique_ptr<ance::TypeDefinition>(new DoubleType())); }

    return instance_;
}
