#include "UnsignedIntegerPointerType.h"

#include "lang/scope/GlobalScope.h"
#include "compiler/Application.h"
#include "compiler/CompileContext.h"

lang::UnsignedIntegerPointerType::UnsignedIntegerPointerType() : TypeDefinition("uiptr") {}

StateCount lang::UnsignedIntegerPointerType::getStateCount() const
{
    return SpecialCount::PLATFORM_DEPENDENT;
}

llvm::Constant* lang::UnsignedIntegerPointerType::getDefaultContent(llvm::LLVMContext& c)
{
    return llvm::ConstantInt::get(getContentType(c), 0, false);
}

llvm::Type* lang::UnsignedIntegerPointerType::getContentType(llvm::LLVMContext&)
{
    return native_type_;
}

llvm::Value* lang::UnsignedIntegerPointerType::buildValue(llvm::Value* pointer, CompileContext* context)
{
    return context->ir()->CreatePtrToInt(pointer, native_type_, pointer->getName() + ".ptrtoint");
}

std::string lang::UnsignedIntegerPointerType::createMangledName()
{
    return getName();
}

llvm::DIType* lang::UnsignedIntegerPointerType::createDebugType(CompileContext* context)
{
    const llvm::DataLayout& dl = context->module()->getDataLayout();

    std::string name         = getName();
    uint64_t    size_in_bits = dl.getTypeSizeInBits(getContentType(*context->llvmContext()));
    auto        encoding     = llvm::dwarf::DW_ATE_unsigned;

    return context->di()->createBasicType(name, size_in_bits, encoding);
}

void lang::UnsignedIntegerPointerType::init(llvm::LLVMContext& llvm_context, llvm::DataLayout& data_layout)
{
    assert(!native_type_);
    native_type_ = llvm::Type::getIntNTy(llvm_context, data_layout.getPointerSizeInBits());
}

lang::ResolvingHandle<lang::Type> lang::UnsignedIntegerPointerType::get()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new UnsignedIntegerPointerType()));
    return instance;
}
