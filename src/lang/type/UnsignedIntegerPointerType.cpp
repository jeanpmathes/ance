#include "UnsignedIntegerPointerType.h"

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/scope/GlobalScope.h"

lang::UnsignedIntegerPointerType::UnsignedIntegerPointerType() : TypeDefinition(lang::Identifier::from("uiptr")) {}

bool lang::UnsignedIntegerPointerType::isUnsignedIntegerPointerType() const
{
    return true;
}

llvm::Value* lang::UnsignedIntegerPointerType::buildValue(llvm::Value* pointer, CompileContext& context)
{
    return context.ir()->CreatePtrToInt(pointer,
                                        get()->getNativeType(*context.llvmContext()),
                                        pointer->getName() + ".ptrtoint");
}

std::string lang::UnsignedIntegerPointerType::createMangledName() const
{
    return std::string(name().text());
}

void lang::UnsignedIntegerPointerType::init(llvm::LLVMContext&, llvm::DataLayout& data_layout)
{
    assert(size_ == 0);

    size_ = std::max(static_cast<unsigned int>(MINIMUM_BIT_SIZE), data_layout.getPointerSizeInBits());
}

unsigned int lang::UnsignedIntegerPointerType::sizeInBits()
{
    assert(size_ != 0);
    return size_;
}

lang::ResolvingHandle<lang::Type> lang::UnsignedIntegerPointerType::get()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new UnsignedIntegerPointerType()));
    return instance;
}

std::optional<size_t> lang::UnsignedIntegerPointerType::getBitSize() const
{
    return std::nullopt;
}

size_t lang::UnsignedIntegerPointerType::getNativeBitSize() const
{
    return size_;
}

bool lang::UnsignedIntegerPointerType::isSigned() const
{
    return false;
}
