#include "VoidType.h"

std::string ance::VoidType::getName()
{
    return "void";
}

llvm::Constant* ance::VoidType::getDefaultContent(llvm::LLVMContext&)
{
    throw std::logic_error("Void does not have a default value.");
}

llvm::Type* ance::VoidType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getVoidTy(c);
}

ance::VoidType* ance::VoidType::get()
{
    if (!instance_)
    {
        instance_ = new ance::VoidType();
    }

    return instance_;
}