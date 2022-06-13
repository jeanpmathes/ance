#include "VoidType.h"

#include "lang/type/Type.h"
#include "compiler/CompileContext.h"

lang::VoidType::VoidType() : TypeDefinition(lang::Identifier::from("void")) {}

StateCount lang::VoidType::getStateCount() const
{
    size_t count = 0;
    return count;
}

llvm::Constant* lang::VoidType::getDefaultContent(llvm::LLVMContext&)
{
    throw std::logic_error("Void does not have a default value.");
}

llvm::Type* lang::VoidType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getVoidTy(c);
}

std::string lang::VoidType::createMangledName()
{
    return std::string(name().text());
}

llvm::DIType* lang::VoidType::createDebugType(CompileContext* context)
{
    return context->di()->createUnspecifiedType(name().text());
}

bool lang::VoidType::isVoidType() const
{
    return true;
}

lang::ResolvingHandle<lang::Type> lang::VoidType::get()
{
    static lang::ResolvingHandle<lang::Type> instance =
        lang::makeHandled<lang::Type>(std::unique_ptr<lang::TypeDefinition>(new VoidType()));
    return instance;
}
