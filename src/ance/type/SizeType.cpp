#include "SizeType.h"

#include <llvm/IR/Constants.h>

#include "ance/scope/GlobalScope.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"

std::string ance::SizeType::getName()
{
    return "size";
}

llvm::Constant* ance::SizeType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantInt::get(getNativeType(c), 0, false);
}

llvm::Type* ance::SizeType::getContentType(llvm::LLVMContext&)
{
    return native_type_;
}

llvm::Value* ance::SizeType::buildValue(llvm::TypeSize size)
{
    return llvm::ConstantInt::get(native_type_, size.getFixedSize(), false);
}

llvm::DIType* ance::SizeType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    std::string name         = getName();
    uint64_t    size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));
    auto        encoding     = llvm::dwarf::DW_ATE_unsigned;

    return context->di()->createBasicType(name, size_in_bits, encoding);
}

void ance::SizeType::init(llvm::LLVMContext& c, Application& app)
{
    assert(!native_type_);
    native_type_ = llvm::Type::getIntNTy(c, app.getBitness());
}

ance::SizeType* ance::SizeType::get()
{
    if (!instance_) { instance_ = new SizeType(); }

    return instance_;
}
