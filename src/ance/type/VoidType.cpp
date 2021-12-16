#include "VoidType.h"

#include "ance/type/Type.h"
#include "compiler/CompileContext.h"

ance::VoidType::VoidType() : TypeDefinition("void") {}

llvm::Constant* ance::VoidType::getDefaultContent(llvm::LLVMContext&)
{
    throw std::logic_error("Void does not have a default value.");
}

llvm::Type* ance::VoidType::getContentType(llvm::LLVMContext& c)
{
    return llvm::Type::getVoidTy(c);
}

std::string ance::VoidType::createMangledName()
{
    return getName();
}

llvm::DIType* ance::VoidType::createDebugType(CompileContext* context)
{
    return context->di()->createUnspecifiedType(getName());
}

bool ance::VoidType::isVoidType() const
{
    return true;
}

ance::ResolvingHandle<ance::Type> ance::VoidType::get()
{
    static ance::ResolvingHandle<ance::Type> instance =
        ance::makeHandled<ance::Type>(std::unique_ptr<ance::TypeDefinition>(new VoidType()));
    return instance;
}
