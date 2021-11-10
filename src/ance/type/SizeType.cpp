#include "SizeType.h"

#include "ance/scope/GlobalScope.h"
#include "ance/type/Type.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"

ance::SizeType::SizeType(std::string name, llvm::Type*& backing) : TypeDefinition(std::move(name)), backing_(backing) {}

llvm::Constant* ance::SizeType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantInt::get(getContentType(c), 0, false);
}

llvm::Type* ance::SizeType::getContentType(llvm::LLVMContext&)
{
    return backing_;
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

    if (backing_ == size_backing_type_) encoding = llvm::dwarf::DW_ATE_unsigned;
    if (backing_ == diff_backing_type_) encoding = llvm::dwarf::DW_ATE_signed;

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

ance::ResolvingHandle<ance::Type> ance::SizeType::getSize()
{
    static ance::ResolvingHandle<ance::Type> instance =
        ance::makeHandled<ance::Type>(std::unique_ptr<ance::TypeDefinition>(new SizeType("size", size_backing_type_)));
    return instance;
}

unsigned int ance::SizeType::getSizeWidth()
{
    return size_width_;
}

ance::ResolvingHandle<ance::Type> ance::SizeType::getDiff()
{
    static ance::ResolvingHandle<ance::Type> instance =
        ance::makeHandled<ance::Type>(std::unique_ptr<ance::TypeDefinition>(new SizeType("diff", diff_backing_type_)));
    return instance;
}

unsigned int ance::SizeType::getDiffWidth()
{
    return diff_width_;
}
