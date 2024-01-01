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

llvm::Constant* lang::OpaquePointerType::getDefaultContent(CompileContext& context) const
{
    return llvm::ConstantPointerNull::get(
        llvm::PointerType::get(llvm::Type::getInt8Ty(context.exec().llvmContext()), 0));
}

llvm::Type* lang::OpaquePointerType::getContentType(CompileContext& context) const
{
    return llvm::PointerType::get(llvm::Type::getInt8Ty(context.exec().llvmContext()), 0);
}

std::string lang::OpaquePointerType::createMangledName() const
{
    return "ptr";
}

Execution::Type lang::OpaquePointerType::createDebugType(CompileContext& context) const
{
    return context.exec().registerOpaqueAddressType(self());
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
