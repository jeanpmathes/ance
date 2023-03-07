#include "OpaquePointerType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/type/Type.h"

lang::OpaquePointerType::OpaquePointerType() : TypeDefinition(lang::Identifier::like("ptr")) {}

bool lang::OpaquePointerType::isOpaquePointerType() const
{
    return true;
}

llvm::Constant* lang::OpaquePointerType::getDefaultContent(llvm::Module& m) const
{
    return llvm::ConstantPointerNull::get(llvm::PointerType::get(llvm::Type::getInt8Ty(m.getContext()), 0));
}

llvm::Type* lang::OpaquePointerType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::PointerType::get(llvm::Type::getInt8Ty(c), 0);
}

std::string lang::OpaquePointerType::createMangledName() const
{
    return "ptr";
}

llvm::DIType* lang::OpaquePointerType::createDebugType(CompileContext& context) const
{
    llvm::DataLayout const& dl = context.llvmModule().getDataLayout();

    uint64_t const size_in_bits = dl.getTypeSizeInBits(getContentType(context.llvmContext()));

    std::string const name     = std::string(this->name().text());
    auto              encoding = llvm::dwarf::DW_ATE_address;

    llvm::DIType* di_type = context.di().createBasicType(name, size_in_bits, encoding);

    return di_type;
}

Optional<lang::ResolvingHandle<lang::Type>> lang::OpaquePointerType::getPointeeType()
{
    return std::nullopt;
}

lang::Type const* lang::OpaquePointerType::getPointeeType() const
{
    return nullptr;
}

lang::ResolvingHandle<lang::Type> lang::OpaquePointerType::clone(lang::Context& new_context) const
{
    return new_context.getOpaquePointerType();
}
