#include "Scope.h"

#include "lang/ApplicationVisitor.h"
#include "lang/scope/LocalScope.h"
#include "lang/type/Type.h"

lang::Scope::Scope() = default;
lang::Scope::Scope(lang::Scope* containing_scope) : containing_scope_(containing_scope) {}

lang::Scope* lang::Scope::scope()
{
    assert(containing_scope_ != nullptr);
    return containing_scope_;
}

lang::Scope const* lang::Scope::scope() const
{
    assert(containing_scope_ != nullptr);
    return containing_scope_;
}

lang::GlobalScope* lang::Scope::getGlobalScope()
{
    return scope()->getGlobalScope();
}

lang::GlobalScope const* lang::Scope::getGlobalScope() const
{
    return scope()->getGlobalScope();
}

lang::OrderedScope* lang::Scope::asOrderedScope()
{
    return nullptr;
}

lang::OrderedScope const* lang::Scope::asOrderedScope() const
{
    auto* self = const_cast<lang::Scope*>(this);
    return self->asOrderedScope();
}

lang::Context& lang::Scope::context()
{
    return getGlobalScope()->context();
}

lang::Context const& lang::Scope::context() const
{
    return getGlobalScope()->context();
}

std::string lang::Scope::getTemporaryName() const
{
    assert(this);// Just to supress warnings that this method could be static.
                 // It is not static because a different naming scheme or thread-safety might be required later.

    static uint64_t temp_name_counter = 0;
    return "$temp" + std::to_string(temp_name_counter++);
}

Owned<lang::OrderedScope> lang::Scope::makeLocalScope()
{
    auto local_scope = makeOwned<lang::LocalScope>(this);
    addChild(*local_scope);

    onSubScope(local_scope.get());

    return local_scope;
}

void lang::Scope::registerUsage(lang::ResolvingHandle<lang::Entity> entity)
{
    used_entities_.emplace_back(entity);
    onRegisterUsage(entity);
}

void lang::Scope::registerUsageIfUndefined(lang::ResolvingHandle<lang::Entity> entity)
{
    if (!entity->isDefined()) { registerUsage(entity); }
}

Optional<lang::OwningHandle<lang::Entity>> lang::Scope::connectWithDefinitionAccordingToOrdering(
    lang::OwningHandle<lang::Entity> entity)
{
    return entity;
}

void lang::Scope::onSubScope(lang::Scope*) {}

void lang::Scope::postResolve()
{
    for (auto& entity : used_entities_)
    {
        if (entity->isDefined()) { addDependency(entity); }
    }
}

void lang::Scope::addDependency(lang::ResolvingHandle<lang::Function> function)
{
    assert(function->isDefined());

    if (function->scope() == this) return;

    if (!function_dependencies_set_.contains(function))
    {
        function_dependencies_set_.emplace(function);
        function_dependencies_.emplace_back(function);
    }

    if (scope() != this) scope()->addDependency(function);
}

void lang::Scope::addDependency(lang::ResolvingHandle<lang::Entity> entity)
{
    assert(entity->isDefined());

    if (entity->scope() == this) return;

    if (!entity_to_dependency_index_.contains(entity))
    {
        entity_to_dependency_index_.emplace(entity, entity_dependencies_.size());
        entity_dependencies_.emplace_back(entity);
    }

    entity_dependencies_[entity_to_dependency_index_.at(entity)].count++;

    if (scope() != this) scope()->addDependency(entity);
}

std::vector<lang::Scope::Dependency<lang::Entity>> lang::Scope::getDependencies()
{
    return entity_dependencies_;
}

std::vector<lang::Scope::Dependency<lang::Variable>> lang::Scope::getVariableDependencies()
{
    std::vector<Dependency<lang::Variable>> result;

    for (auto& dependency : entity_dependencies_)
    {
        if (lang::Type::isMatching<lang::Variable>(dependency.entity))
        {
            result.emplace_back(lang::Type::makeMatching<Variable>(dependency.entity), dependency.count);
        }
    }

    return result;
}

std::vector<lang::Scope::Dependency<lang::FunctionGroup>> lang::Scope::getFunctionGroupDependencies()
{
    std::vector<Dependency<lang::FunctionGroup>> result;

    for (auto& dependency : entity_dependencies_)
    {
        if (lang::Type::isMatching<lang::FunctionGroup>(dependency.entity))
        {
            result.emplace_back(lang::Type::makeMatching<FunctionGroup>(dependency.entity), dependency.count);
        }
    }

    return result;
}

std::vector<lang::Scope::Dependency<lang::Type>> lang::Scope::getTypeDependencies()
{
    std::vector<Dependency<lang::Type>> result;

    for (auto& dependency : entity_dependencies_)
    {
        if (lang::Type::isMatching<lang::Type>(dependency.entity))
        {
            result.emplace_back(lang::Type::makeMatching<Type>(dependency.entity), dependency.count);
        }
    }

    return result;
}

std::vector<lang::ResolvingHandle<lang::Function>> lang::Scope::getFunctionDependencies()
{
    return function_dependencies_;
}
