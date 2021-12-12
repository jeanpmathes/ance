#include "TypeDefinition.h"

#include <set>
#include <stack>

#include "ance/type/Type.h"
#include "ance/type/VoidType.h"
#include "validation/ValidationLogger.h"

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

bool ance::TypeDefinition::isIntegerType() const
{
    return false;
}

bool ance::TypeDefinition::isIntegerType(uint64_t, bool) const
{
    return false;
}

bool ance::TypeDefinition::isBooleanType() const
{
    return false;
}

bool ance::TypeDefinition::isFloatingPointType() const
{
    return false;
}

bool ance::TypeDefinition::isFloatingPointType(size_t) const
{
    return false;
}

bool ance::TypeDefinition::isSizeType() const
{
    return false;
}

bool ance::TypeDefinition::isDiffType() const
{
    return false;
}

bool ance::TypeDefinition::isVoidType() const
{
    return false;
}

bool ance::TypeDefinition::isPointerType() const
{
    return false;
}

bool ance::TypeDefinition::isReferenceType() const
{
    return false;
}

ance::ResolvingHandle<ance::Type> ance::TypeDefinition::getElementType() const
{
    return ance::VoidType::get();
}

void ance::TypeDefinition::setType(ance::Type* type)
{
    assert(!type_);
    type_ = type;
}

ance::ResolvingHandle<ance::Type> ance::TypeDefinition::getActualType()
{
    return self();
}

ance::ResolvingHandle<ance::Type> ance::TypeDefinition::getOriginalType()
{
    return self();
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

bool ance::TypeDefinition::isImplicitlyConvertibleTo(ance::ResolvingHandle<ance::Type>)
{
    return false;
}

std::shared_ptr<ance::Value> ance::TypeDefinition::convertImplicitlyTo(ance::ResolvingHandle<ance::Type>,
                                                                       std::shared_ptr<Value>,
                                                                       CompileContext*)
{
    return {};
}

bool ance::TypeDefinition::isImplicitlyConvertibleFrom(ance::ResolvingHandle<ance::Type>)
{
    return false;
}

std::shared_ptr<ance::Value> ance::TypeDefinition::convertImplicitlyFrom(std::shared_ptr<Value>,
                                                                         ance::ResolvingHandle<ance::Type>,
                                                                         CompileContext*)
{
    return {};
}

bool ance::TypeDefinition::checkDependencies(ValidationLogger& validation_logger)
{
    std::stack<ance::TypeDefinition*> to_check;
    std::set<ance::TypeDefinition*>   checked;

    to_check.push(this);

    while (!to_check.empty())
    {
        ance::TypeDefinition* current = to_check.top();
        to_check.pop();

        if (checked.find(current) != checked.end())
        {
            validation_logger.logError("Type '" + getName() + "' has circular dependency",
                                       current->getDefinitionLocation());
            return false;
        }

        checked.insert(current);

        for (auto& dependency : current->getDependencies()) { to_check.push(dependency); }
    }

    return true;
}

std::vector<ance::TypeDefinition*> ance::TypeDefinition::getDependencies()
{
    return {};
}

ance::ResolvingHandle<ance::Type> ance::TypeDefinition::self()
{
    assert(type_);
    return type_->self();
}
