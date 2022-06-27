#include "TypeDefinition.h"

#include <set>
#include <map>
#include <stack>

#include "lang/type/Type.h"
#include "lang/type/VoidType.h"
#include "validation/ValidationLogger.h"

lang::TypeDefinition::TypeDefinition(lang::Identifier name, lang::Location location)
    : name_(std::move(name))
    , location_(location)
{}

const lang::Identifier& lang::TypeDefinition::name() const
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

bool lang::TypeDefinition::hasMember(const lang::Identifier&)
{
    return false;
}

lang::ResolvingHandle<lang::Type> lang::TypeDefinition::getMemberType(const lang::Identifier&)
{
    return lang::VoidType::get();
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

bool lang::TypeDefinition::validateMemberAccess(const lang::Identifier&, ValidationLogger&)
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

std::shared_ptr<lang::Value> lang::TypeDefinition::buildMemberAccess(std::shared_ptr<Value>,
                                                                     const lang::Identifier&,
                                                                     CompileContext*)
{
    return nullptr;
}

bool lang::TypeDefinition::checkDependencies(ValidationLogger& validation_logger)
{
    const int visited  = 1;
    const int finished = 2;

    std::stack<std::pair<lang::TypeDefinition*, bool>> to_check;
    std::map<lang::TypeDefinition*, int>               state;

    to_check.emplace(this, false);

    while (!to_check.empty())
    {
        auto& [current, visited_children] = to_check.top();

        if (visited_children)
        {
            to_check.pop();
            state[current] = finished;
        }
        else {
            to_check.top() = std::make_pair(current, true);

            if (state[current] == visited)
            {
                validation_logger.logError("Type " + self()->getAnnotatedName(false) + " has circular dependency",
                                           this->getDefinitionLocation());
                return false;
            }

            state[current] = visited;

            for (auto& dependency : current->getDependencies())
            {
                if (state[dependency] == finished) continue;
                to_check.emplace(dependency, false);
            }
        }
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
