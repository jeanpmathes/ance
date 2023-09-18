#include "Scope.h"

#include "lang/ApplicationVisitor.h"
#include "lang/scope/LocalScope.h"
#include "lang/type/Type.h"

lang::Scope::Scope() = default;
lang::Scope::Scope(lang::Scope* containing_scope) : containing_scope_(containing_scope)
{
    assert(containing_scope != nullptr);
}

void lang::Scope::setContainingScope(lang::Scope& containing_scope)
{

    containing_scope_ = &containing_scope;
}

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

Owned<lang::OrderedScope> lang::Scope::makeLocalScope(lang::CodeBlock& code_block)
{
    auto local_scope = makeOwned<lang::LocalScope>(this, code_block);
    addChild(*local_scope);
    return local_scope;
}

void lang::Scope::registerUsage(lang::ResolvingHandle<lang::Entity> entity, bool is_only_declared)
{
    if (auto type = entity.as<lang::Type>(); type.hasValue())
    {
        if ((**type).getDefinition() == nullptr)
        {
            if (!(**type).isDefined()) { onRegisterUsage(*type); }
            addDependency(*type, is_only_declared);
        }
        else
        {
            for (auto& extracted : (**type).getDeclarationDependencies())
            {
                if (!extracted->isDefined()) { onRegisterUsage(extracted); }
                addDependency(extracted, true);
            }
            for (auto& extracted : (**type).getDefinitionDependencies())
            {
                if (!extracted->isDefined()) { onRegisterUsage(extracted); }
                addDependency(extracted, true);
            }
        }
    }
    else
    {
        if (!entity->isDefined()) { onRegisterUsage(entity); }
        addDependency(entity, is_only_declared);
    }
}

Optional<lang::OwningHandle<lang::Entity>> lang::Scope::connectWithDefinitionAccordingToOrdering(
    lang::OwningHandle<lang::Entity> entity)
{
    return entity;
}

void lang::Scope::postResolve()
{}

void lang::Scope::addDependency(lang::ResolvingHandle<lang::Entity> entity, bool is_only_declared)
{
    if (is_only_declared)
    {
        if (!entity_to_declaration_dependency_index_.contains(entity))
        {
            entity_to_declaration_dependency_index_.emplace(entity, entity_declaration_dependencies_.size());
            entity_declaration_dependencies_.emplace_back(entity);
        }

        entity_declaration_dependencies_[entity_to_declaration_dependency_index_.at(entity)].count++;
    }
    else
    {
        if (!entity_to_definition_dependency_index_.contains(entity))
        {
            entity_to_definition_dependency_index_.emplace(entity, entity_definition_dependencies_.size());
            entity_definition_dependencies_.emplace_back(entity);
        }

        entity_definition_dependencies_[entity_to_definition_dependency_index_.at(entity)].count++;
    }

    if (scope() != this) scope()->addDependency(entity, is_only_declared);
}

std::vector<lang::Scope::Dependency<lang::Entity>> lang::Scope::getDependenciesOnDeclaration()
{
    return entity_declaration_dependencies_;
}

std::vector<std::reference_wrapper<const lang::Entity>> lang::Scope::getDependenciesOnDeclaration() const
{
    std::vector<std::reference_wrapper<const lang::Entity>> result;
    result.reserve(entity_declaration_dependencies_.size());

    for (auto& dependency : entity_declaration_dependencies_) { result.emplace_back(dependency.entity); }

    return result;
}

std::vector<lang::Scope::Dependency<lang::Entity>> lang::Scope::getDependenciesOnDefinition()
{
    return entity_definition_dependencies_;
}

std::vector<std::reference_wrapper<const lang::Entity>> lang::Scope::getDependenciesOnDefinition() const
{
    std::vector<std::reference_wrapper<const lang::Entity>> result;
    result.reserve(entity_definition_dependencies_.size());

    for (auto& dependency : entity_definition_dependencies_) { result.emplace_back(dependency.entity); }

    return result;
}
