#include "VoidType.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Function.h"
#include "lang/type/Type.h"

lang::VoidType::VoidType() : TypeDefinition(lang::Identifier::from("void")) {}

StateCount lang::VoidType::getStateCount() const
{
    size_t count = 0;
    return count;
}

llvm::Constant* lang::VoidType::getDefaultContent(llvm::Module&)
{
    throw std::logic_error("Void does not have a default value.");
}

llvm::Type* lang::VoidType::getContentType(llvm::LLVMContext& c) const
{
    return llvm::Type::getVoidTy(c);
}

std::string lang::VoidType::createMangledName() const
{
    return std::string(name().text());
}

llvm::DIType* lang::VoidType::createDebugType(CompileContext& context)
{
    return context.di()->createUnspecifiedType(name().text());
}

bool lang::VoidType::isVoidType() const
{
    return true;
}

void lang::VoidType::buildDefaultInitializer(llvm::Value*, llvm::Value*, CompileContext&)
{
    throw std::logic_error("Void does not have a default value.");
}

void lang::VoidType::buildCopyInitializer(llvm::Value*, llvm::Value*, CompileContext&)
{
    throw std::logic_error("Void does not have a copy value.");
}

void lang::VoidType::buildFinalizer(llvm::Value*, llvm::Value*, CompileContext&)
{
    throw std::logic_error("Void does not have a finalizer.");
}

void lang::VoidType::createConstructors() {}

void lang::VoidType::buildNativeDeclaration(CompileContext&) {}

void lang::VoidType::buildNativeDefinition(CompileContext&) {}

lang::ResolvingHandle<lang::Type> lang::VoidType::get()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new VoidType()));
    return instance;
}
