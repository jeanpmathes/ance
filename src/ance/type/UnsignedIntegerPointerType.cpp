#include "UnsignedIntegerPointerType.h"

#include "Application.h"
#include "GlobalScope.h"

std::string ance::UnsignedIntegerPointerType::getName()
{
    return "uiptr";
}

llvm::Constant* ance::UnsignedIntegerPointerType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantInt::get(getNativeType(c), 0, false);
}

llvm::Type* ance::UnsignedIntegerPointerType::getContentType(llvm::LLVMContext&)
{
    return native_type_;
}

llvm::Value* ance::UnsignedIntegerPointerType::buildValue(
    llvm::Value* pointer,
    llvm::LLVMContext&,
    llvm::Module*,
    CompileContext*,
    llvm::IRBuilder<>& ir,
    llvm::DIBuilder*)
{
    return ir.CreatePtrToInt(pointer, native_type_);
}

void ance::UnsignedIntegerPointerType::init(llvm::LLVMContext& c, Application& app)
{
    assert(!native_type_);
    native_type_ = llvm::Type::getIntNTy(c, app.getBitness());
}

ance::UnsignedIntegerPointerType* ance::UnsignedIntegerPointerType::get()
{
    if (!instance_)
    {
        instance_ = new UnsignedIntegerPointerType();
    }

    return instance_;
}
