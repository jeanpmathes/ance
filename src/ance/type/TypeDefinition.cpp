#include "TypeDefinition.h"

ance::TypeDefinition::TypeDefinition(std::string name) : name_(std::move(name)) {}

const std::string& ance::TypeDefinition::getName() const
{
    return name_;
}

llvm::Type* ance::TypeDefinition::getNativeType(llvm::LLVMContext& c)
{
    return llvm::PointerType::get(getContentType(c), 0);
}

llvm::DIType* ance::TypeDefinition::getDebugType(CompileContext* context)
{
    if (!debug_type_) { debug_type_ = createDebugType(context); }

    return debug_type_;
}

llvm::TypeSize ance::TypeDefinition::getNativeSize(llvm::Module* m)
{
    return m->getDataLayout().getTypeAllocSize(getNativeType(m->getContext()));
}

llvm::TypeSize ance::TypeDefinition::getContentSize(llvm::Module* m)
{
    return m->getDataLayout().getTypeAllocSize(getContentType(m->getContext()));
}

bool ance::TypeDefinition::isSubscriptDefined()
{
    return false;
}

ance::Type* ance::TypeDefinition::getSubscriptReturnType()
{
    return nullptr;
}

bool ance::TypeDefinition::validate(ValidationLogger&, ance::Location)
{
    return true;
}

bool ance::TypeDefinition::validateSubscript(Type*, ance::Location, Type*, ance::Location, ValidationLogger&)
{
    return false;
}

std::shared_ptr<ance::Value> ance::TypeDefinition::buildSubscript(std::shared_ptr<Value>,
                                                                  std::shared_ptr<Value>,
                                                                  CompileContext*)
{
    return nullptr;
}
