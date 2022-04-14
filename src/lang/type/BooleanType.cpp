#include "BooleanType.h"

#include "compiler/CompileContext.h"
#include "lang/type/Type.h"

lang::BooleanType::BooleanType() : TypeDefinition("bool") {}

StateCount lang::BooleanType::getStateCount() const
{
    size_t count = 2;
    return count;
}

bool lang::BooleanType::isBooleanType() const
{
    return true;
}

llvm::Constant* lang::BooleanType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantInt::get(getContentType(c), 0, false);
}

llvm::Type* lang::BooleanType::getContentType(llvm::LLVMContext& c)
{
    if (!native_type_) { native_type_ = llvm::Type::getInt1Ty(c); }

    return native_type_;
}

std::string lang::BooleanType::createMangledName()
{
    return "b";
}

llvm::DIType* lang::BooleanType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    std::string name         = getName();
    uint64_t    size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));

    return context->di()->createBasicType(name, size_in_bits, llvm::dwarf::DW_ATE_boolean);
}

lang::ResolvingHandle<lang::Type> lang::BooleanType::get()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new BooleanType()));
    return instance;
}
