#include "SizeType.h"

#include "ance/scope/GlobalScope.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"

ance::SizeType::SizeType(std::string name) : Type(std::move(name)) {}

llvm::Constant* ance::SizeType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantInt::get(getContentType(c), 0, false);
}

llvm::Type* ance::SizeType::getContentType(llvm::LLVMContext&)
{
    if (this == size_instance_) return size_backing_type_;
    if (this == diff_instance_) return diff_backing_type_;

    return nullptr;
}

llvm::Value* ance::SizeType::buildValue(llvm::TypeSize size)
{
    return llvm::ConstantInt::get(size_backing_type_, size.getFixedSize(), false);
}

llvm::DIType* ance::SizeType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    std::string           name         = getName();
    uint64_t              size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));
    llvm::dwarf::TypeKind encoding;

    if (this == size_instance_) encoding = llvm::dwarf::DW_ATE_unsigned;
    if (this == diff_instance_) encoding = llvm::dwarf::DW_ATE_signed;

    return context->di()->createBasicType(name, size_in_bits, encoding);
}

void ance::SizeType::init(llvm::LLVMContext& c, Application& app)
{
    assert(!size_backing_type_);
    assert(!diff_backing_type_);

    size_width_ = app.getBitness();
    diff_width_ = size_width_ * 2;

    size_backing_type_ = llvm::Type::getIntNTy(c, size_width_);
    diff_backing_type_ = llvm::Type::getIntNTy(c, diff_width_);
}

ance::SizeType* ance::SizeType::getSize()
{
    if (!size_instance_) { size_instance_ = new SizeType("size"); }

    return size_instance_;
}

unsigned int ance::SizeType::getSizeWidth()
{
    return size_width_;
}

ance::SizeType* ance::SizeType::getDiff()
{
    if (!diff_instance_) { diff_instance_ = new SizeType("diff"); }

    return diff_instance_;
}

unsigned int ance::SizeType::getDiffWidth()
{
    return diff_width_;
}
