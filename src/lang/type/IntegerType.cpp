#include "IntegerType.h"

#include "compiler/CompileContext.h"

StateCount lang::IntegerType::getStateCount() const
{
    auto bit_size = getBitSize();
    if (bit_size.has_value())
    {
        size_t state_count = 1 << bit_size.value();
        return state_count;
    }

    return SpecialCount::PLATFORM_DEPENDENT;
}

llvm::Constant* lang::IntegerType::getDefaultContent(llvm::Module& m)
{
    return llvm::ConstantInt::get(getContentType(m.getContext()), 0, false);
}

llvm::Type* lang::IntegerType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::Type::getIntNTy(c, static_cast<unsigned>(getNativeBitSize()));
}

bool lang::IntegerType::isTriviallyDefaultConstructible() const
{
    return true;
}

bool lang::IntegerType::isTriviallyCopyConstructible() const
{
    return true;
}

bool lang::IntegerType::isTriviallyDestructible() const
{
    return true;
}

llvm::DIType* lang::IntegerType::createDebugType(CompileContext& context)
{
    const llvm::DataLayout& dl = context.module()->getDataLayout();

    std::string name         = std::string(this->name().text());
    uint64_t    size_in_bits = dl.getTypeSizeInBits(getContentType(*context.llvmContext()));
    auto        encoding     = isSigned() ? llvm::dwarf::DW_ATE_signed : llvm::dwarf::DW_ATE_unsigned;

    return context.di()->createBasicType(name, size_in_bits, encoding);
}
