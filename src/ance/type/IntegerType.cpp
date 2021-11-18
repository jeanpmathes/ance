#include "IntegerType.h"

#include "ance/scope/GlobalScope.h"
#include "ance/type/Type.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"

ance::IntegerType::IntegerType(uint64_t bit_size, bool is_signed)
    : TypeDefinition((is_signed ? "i" : "ui") + std::to_string(bit_size))
    , bit_size_(bit_size)
    , is_signed_(is_signed)
{}

llvm::Constant* ance::IntegerType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantInt::get(getContentType(c), 0, is_signed_);
}

llvm::Type* ance::IntegerType::getContentType(llvm::LLVMContext& c)
{
    if (!type_) { type_ = llvm::Type::getIntNTy(c, bit_size_); }

    return type_;
}

llvm::DIType* ance::IntegerType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    std::string name         = getName();
    uint64_t    size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));
    auto        encoding     = is_signed_ ? llvm::dwarf::DW_ATE_signed : llvm::dwarf::DW_ATE_unsigned;

    return context->di()->createBasicType(name, size_in_bits, encoding);
}

ance::TypeRegistry<std::pair<uint64_t, bool>>& ance::IntegerType::getIntegerTypes()
{
    static TypeRegistry<std::pair<uint64_t, bool>> integer_types;
    return integer_types;
}

ance::TypeDefinitionRegistry* ance::IntegerType::getRegistry()
{
    return &getIntegerTypes();
}

ance::ResolvingHandle<ance::Type> ance::IntegerType::get(uint64_t bit_size, bool is_signed)
{
    std::vector<ance::ResolvingHandle<ance::Type>> used_types;

    std::optional<ance::ResolvingHandle<ance::Type>> defined_type =
        getIntegerTypes().get(used_types, std::make_pair(bit_size, is_signed));

    if (defined_type.has_value()) { return defined_type.value(); }
    else
    {
        auto*                             integer_type = new ance::IntegerType(bit_size, is_signed);
        ance::ResolvingHandle<ance::Type> type =
            ance::makeHandled<ance::Type>(std::unique_ptr<ance::IntegerType>(integer_type));
        getIntegerTypes().add(std::move(used_types), std::make_pair(bit_size, is_signed), type);

        return type;
    }
}

bool ance::IntegerType::isIntegerType(ance::ResolvingHandle<ance::Type> type, uint64_t bit_size, bool is_signed)
{
    auto* integer_type = dynamic_cast<ance::IntegerType*>(type->getDefinition());
    if (!integer_type) return false;

    return integer_type->bit_size_ == bit_size && integer_type->is_signed_ == is_signed;
}
