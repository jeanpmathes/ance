#include "TypeDefinition.h"

#include <set>
#include <stack>

#include "lang/type/Type.h"
#include "lang/type/VoidType.h"
#include "validation/ValidationLogger.h"

lang::TypeDefinition::TypeDefinition(std::string name, lang::Location location)
    : name_(std::move(name))
    , location_(location)
{}

const std::string& lang::TypeDefinition::name() const
{
    return name_;
}

const std::string& lang::TypeDefinition::getMangledName()
{
    if (mangled_name_.empty()) { mangled_name_ = createMangledName(); }

    return mangled_name_;
}

lang::Location lang::TypeDefinition::getDefinitionLocation() const
{
    return location_;
}

bool lang::TypeDefinition::isCustom() const
{
    return !location_.isGlobal();
}

bool lang::TypeDefinition::isIntegerType() const
{
    return false;
}

bool lang::TypeDefinition::isIntegerType(uint64_t, bool) const
{
    return false;
}

bool lang::TypeDefinition::isBooleanType() const
{
    return false;
}

bool lang::TypeDefinition::isFloatingPointType() const
{
    return false;
}

bool lang::TypeDefinition::isFloatingPointType(size_t) const
{
    return false;
}

bool lang::TypeDefinition::isSizeType() const
{
    return false;
}

bool lang::TypeDefinition::isDiffType() const
{
    return false;
}

bool lang::TypeDefinition::isVoidType() const
{
    return false;
}

bool lang::TypeDefinition::isPointerType() const
{
    return false;
}

bool lang::TypeDefinition::isReferenceType() const
{
    return false;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getElementType() const
{
    return lang::VoidType::get();
}

void lang::TypeDefinition::setType(lang::Type* type)
{
    assert(!type_);
    type_ = type;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getActualType() const
{
    return self();
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getOriginalType() const
{
    return self();
}

void lang::TypeDefinition::setContainingScope(lang::Scope* scope)
{
    assert(!containing_scope_);
    containing_scope_ = scope;

    onScope();
}

void lang::TypeDefinition::onScope() {}

lang::Scope* lang::TypeDefinition::scope()
{
    assert(containing_scope_);
    return containing_scope_;
}

llvm::Type* lang::TypeDefinition::getNativeType(llvm::LLVMContext& c)
{
    return llvm::PointerType::get(getContentType(c), 0);
}

llvm::DIType* lang::TypeDefinition::getDebugType(CompileContext* context)
{
    if (!debug_type_) { debug_type_ = createDebugType(context); }

    return debug_type_;
}

llvm::TypeSize lang::TypeDefinition::getNativeSize(llvm::Module* m)
{
    if (self() == lang::VoidType::get()) return llvm::TypeSize::getNull();

    return m->getDataLayout().getTypeAllocSize(getNativeType(m->getContext()));
}

llvm::TypeSize lang::TypeDefinition::getContentSize(llvm::Module* m)
{
    if (self() == lang::VoidType::get()) return llvm::TypeSize::getNull();

    return m->getDataLayout().getTypeAllocSize(getContentType(m->getContext()));
}

bool lang::TypeDefinition::isSubscriptDefined()
{
    return false;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getSubscriptReturnType()
{
    return lang::VoidType::get();
}

bool lang::TypeDefinition::isOperatorDefined(lang::BinaryOperator, lang::ResolvingHandle<lang::Type>)
{
    return false;
}

bool lang::TypeDefinition::isOperatorDefined(lang::UnaryOperator)
{
    return false;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getOperatorResultType(lang::BinaryOperator,
                                                                              lang::ResolvingHandle<lang::Type>)
{
    return lang::VoidType::get();
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getOperatorResultType(lang::UnaryOperator)
{
    return lang::VoidType::get();
}

bool lang::TypeDefinition::isImplicitlyConvertibleTo(lang::ResolvingHandle<lang::Type>)
{
    return false;
}

bool lang::TypeDefinition::validateDefinition(ValidationLogger&)
{
    return true;
}

bool lang::TypeDefinition::validate(ValidationLogger&, lang::Location)
{
    return true;
}

bool lang::TypeDefinition::validateSubscript(lang::Location,
                                             lang::ResolvingHandle<lang::Type>,
                                             lang::Location,
                                             ValidationLogger&)
{
    return false;
}

bool lang::TypeDefinition::validateOperator(lang::BinaryOperator,
                                            lang::ResolvingHandle<lang::Type>,
                                            lang::Location,
                                            lang::Location,
                                            ValidationLogger&)
{
    return false;
}

bool lang::TypeDefinition::validateOperator(lang::UnaryOperator, lang::Location, ValidationLogger&)
{
    return false;
}

bool lang::TypeDefinition::validateImplicitConversion(lang::ResolvingHandle<lang::Type>,
                                                      lang::Location,
                                                      ValidationLogger&)
{
    return false;
}

std::shared_ptr<lang::Value> lang::TypeDefinition::buildSubscript(std::shared_ptr<Value>,
                                                                  std::shared_ptr<Value>,
                                                                  CompileContext*)
{
    return nullptr;
}

std::shared_ptr<lang::Value> lang::TypeDefinition::buildOperator(lang::BinaryOperator,
                                                                 std::shared_ptr<Value>,
                                                                 std::shared_ptr<Value>,
                                                                 CompileContext*)
{
    return nullptr;
}

std::shared_ptr<lang::Value> lang::TypeDefinition::buildOperator(lang::UnaryOperator,
                                                                 std::shared_ptr<Value>,
                                                                 CompileContext*)
{
    return nullptr;
}

std::shared_ptr<lang::Value> lang::TypeDefinition::buildImplicitConversion(lang::ResolvingHandle<lang::Type>,
                                                                           std::shared_ptr<Value>,
                                                                           CompileContext*)
{
    return nullptr;
}

bool lang::TypeDefinition::checkDependencies(ValidationLogger& validation_logger)
{
    std::stack<lang::TypeDefinition*> to_check;
    std::set<lang::TypeDefinition*>   checked;

    to_check.push(this);

    while (!to_check.empty())
    {
        lang::TypeDefinition* current = to_check.top();
        to_check.pop();

        if (checked.find(current) != checked.end())
        {
            validation_logger.logError("Type " + self()->getAnnotatedName() + " has circular dependency",
                                       current->getDefinitionLocation());
            return false;
        }

        checked.insert(current);

        for (auto& dependency : current->getDependencies()) { to_check.push(dependency); }
    }

    return true;
}

std::vector<lang::TypeDefinition*> lang::TypeDefinition::getDependencies()
{
    return {};
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::self() const
{
    assert(type_);
    return type_->self();
}
