#include "VoidType.h"

#include "compiler/CompileContext.h"

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

llvm::DIType* ance::VoidType::createDebugType(CompileContext* context)
{
    return context->di()->createUnspecifiedType(getName());
}

ance::VoidType* ance::VoidType::get()
{
    if (!instance_) { instance_ = new ance::VoidType(); }

    return instance_;
}
