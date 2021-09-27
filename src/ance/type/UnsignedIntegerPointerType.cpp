#include "UnsignedIntegerPointerType.h"

#include "ance/scope/GlobalScope.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"

std::string ance::UnsignedIntegerPointerType::getName()
{
    return "uiptr";
}

llvm::Constant* ance::UnsignedIntegerPointerType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantInt::get(getContentType(c), 0, false);
}

llvm::Type* ance::UnsignedIntegerPointerType::getContentType(llvm::LLVMContext&)
{
    return native_type_;
}

llvm::Value* ance::UnsignedIntegerPointerType::buildValue(llvm::Value* pointer,
                                                          llvm::LLVMContext&,
                                                          llvm::Module*,
                                                          CompileContext*,
                                                          llvm::IRBuilder<>& ir,
                                                          llvm::DIBuilder*)
{
    return ir.CreatePtrToInt(pointer, native_type_);
}

llvm::DIType* ance::UnsignedIntegerPointerType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    std::string name         = getName();
    uint64_t    size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));
    auto        encoding     = llvm::dwarf::DW_ATE_unsigned;

    return context->di()->createBasicType(name, size_in_bits, encoding);
}

void ance::UnsignedIntegerPointerType::init(llvm::LLVMContext& llvm_context, llvm::DataLayout& data_layout)
{
    assert(!native_type_);
    native_type_ = llvm::Type::getIntNTy(llvm_context, data_layout.getMaxPointerSizeInBits());
}

ance::UnsignedIntegerPointerType* ance::UnsignedIntegerPointerType::get()
{
    if (!instance_) { instance_ = new UnsignedIntegerPointerType(); }

    return instance_;
}
