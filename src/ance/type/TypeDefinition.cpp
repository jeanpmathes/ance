#include "TypeDefinition.h"

#include "ance/type/VoidType.h"

ance::TypeDefinition::TypeDefinition(std::string name, ance::Location location)
    : name_(std::move(name))
    , location_(location)
{}

const std::string& ance::TypeDefinition::getName() const
{
    return name_;
}

ance::Location ance::TypeDefinition::getDefinitionLocation() const
{
    return location_;
}

bool ance::TypeDefinition::isCustom() const
{
    return !location_.isGlobal();
}

void ance::TypeDefinition::setContainingScope(ance::Scope* scope)
{
    assert(!containing_scope_);
    containing_scope_ = scope;

    onScope();
}

void ance::TypeDefinition::onScope() {}

ance::Scope* ance::TypeDefinition::scope()
{
    assert(containing_scope_);
    return containing_scope_;
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

ance::ResolvingHandle<ance::Type> ance::TypeDefinition::getSubscriptReturnType()
{
    return ance::VoidType::get();
}

bool ance::TypeDefinition::validateDefinition(ValidationLogger&)
{
    return true;
}

bool ance::TypeDefinition::validate(ValidationLogger&, ance::Location)
{
    return true;
}

bool ance::TypeDefinition::validateSubscript(ance::Location,
                                             ance::ResolvingHandle<ance::Type>,
                                             ance::Location,
                                             ValidationLogger&)
{
    return false;
}

std::shared_ptr<ance::Value> ance::TypeDefinition::buildSubscript(std::shared_ptr<Value>,
                                                                  std::shared_ptr<Value>,
                                                                  CompileContext*)
{
    return nullptr;
}
