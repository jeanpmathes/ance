#include "OrderedScope.h"

#include "lang/ApplicationVisitor.h"

lang::OrderedScope* lang::OrderedScope::asOrderedScope()
{
    return this;
}

bool lang::OrderedScope::isNameConflicted(lang::Identifier const& name) const
{
    return scope().isNameConflicted(name);// Redefinition allowed, so no conflict.
}

void lang::OrderedScope::addDescription(Owned<lang::Description> description)
{
    descriptions_[description->name()].emplace_back(std::move(description));
}

void lang::OrderedScope::addEntity(lang::OwningHandle<lang::Entity> entity)
{
    assert(blockers_.contains(entity->name()));

    active_entities_.insert_or_assign(entity->name(), entity.handle());
    defined_entities_[entity->name()].emplace_back(std::move(entity));
}

void lang::OrderedScope::prepareDefinition(lang::Identifier name)
{
    blockers_.emplace(name);
}

bool lang::OrderedScope::erase(lang::ResolvingHandle<lang::Entity> entity)
{
    if (!entity->isDefined() || !active_entities_.contains(entity->name())) return false;

    active_entities_.erase(entity->name());

    return true;
}

bool lang::OrderedScope::wasEntityErased(lang::Entity const& entity) const
{
    return !active_entities_.contains(entity.name()) && defined_entities_.contains(entity.name());
}

void lang::OrderedScope::onRegisterUsage(lang::ResolvingHandle<lang::Entity> entity)
{
    assert(!entity->isDefined());

    if (undefined_entities_.contains(entity->name()))
    {
        entity.reroute(undefined_entities_.at(entity->name()).handle());
        return;
    }

    lang::Scope*                         current      = this;
    Optional<OwningHandle<lang::Entity>> owned_entity = lang::OwningHandle<lang::Entity>::takeOwnership(entity);

    while (current != &current->scope())
    {
        owned_entity = current->connectWithDefinitionAccordingToOrdering(std::move(owned_entity.value()));
        if (!owned_entity.hasValue()) return;
        current = &current->scope();
    }

    undefined_entities_.emplace(entity->name(), std::move(owned_entity.value()));
}

Optional<lang::OwningHandle<lang::Entity>> lang::OrderedScope::connectWithDefinitionAccordingToOrdering(
    lang::OwningHandle<lang::Entity> variable)
{
    auto it = active_entities_.find(variable->name());

    if (it != active_entities_.end())
    {
        variable.handle().reroute(it->second);
        return std::nullopt;
    }

    if (blockers_.contains(variable->name()))
    {
        if (blocked_entities_.contains(variable->name()))
        {
            variable.handle().reroute(blocked_entities_.at(variable->name()).handle());
        }
        else { blocked_entities_.emplace(variable->name(), std::move(variable)); }

        return std::nullopt;
    }

    return variable;
}

void lang::OrderedScope::resolve()
{
    resolveFollowingOrder();

    lang::Scope& parent = scope();

    auto iterator = undefined_entities_.begin();

    while (iterator != undefined_entities_.end())
    {
        auto& [name, entity] = *iterator;

        if (parent.resolveDefinition(entity.handle())) { iterator = undefined_entities_.erase(iterator); }
        else { ++iterator; }
    }
}

void lang::OrderedScope::postResolve()
{
    // Nothing to do.

    Scope::postResolve();
}

bool lang::OrderedScope::resolveDefinition(lang::ResolvingHandle<lang::Entity> entity)
{
    // If the entity were defined in this scope, we would have found it when registering the usage.
    return scope().resolveDefinition(entity);
}

void lang::OrderedScope::buildEntityDeclarations(CompileContext& context) const
{
    for (auto& [name, entities] : defined_entities_)
    {
        for (auto& entity : entities)
        {
            lang::Variable const* variable = dynamic_cast<lang::Variable const*>(&*entity);

            if (variable != nullptr) { variable->buildDeclaration(context); }
        }
    }

    buildEntityDeclarationsFollowingOrder(context);
}

void lang::OrderedScope::buildEntityFinalizations(CompileContext& context) const
{
    for (auto& [name, entity] : active_entities_)
    {
        lang::Variable const* variable = entity.as<lang::Variable>();
        if (variable != nullptr) { variable->buildFinalization(context); }
    }
}
