#include "UnorderedScope.h"

#include <iostream>
#include <sstream>
#include <string>

#include "lang/ApplicationVisitor.h"
#include "lang/construct/descriptions/Description.h"
#include "lang/utility/SortingGraph.h"
#include "validation/ValidationLogger.h"

bool lang::UnorderedScope::isNameConflicted(lang::Identifier const& name) const
{
    return incompatible_descriptions_.contains(name);
}

void lang::UnorderedScope::addDescription(Owned<lang::Description> description)
{
    addChild(*description);

    if (incompatible_descriptions_.contains(description->name()))
    {
        incompatible_descriptions_[description->name()].emplace_back(context().getCurrentDescriptionSourceName(),
                                                                     std::move(description));
        return;
    }

    auto conflict = compatible_descriptions_.find(description->name());

    if (conflict != compatible_descriptions_.end())
    {
        auto& [name, conflicting_description] = *conflict;

        assert(not conflicting_description.empty());

        bool const is_overload_allowed =
            description->isOverloadAllowed() && conflicting_description.front().description->isOverloadAllowed();

        if (not is_overload_allowed)
        {
            std::move(conflicting_description.begin(),
                      conflicting_description.end(),
                      std::back_inserter(incompatible_descriptions_[description->name()]));
            incompatible_descriptions_[description->name()].emplace_back(context().getCurrentDescriptionSourceName(),
                                                                         std::move(description));

            compatible_descriptions_.erase(conflict);

            return;
        }
    }

    compatible_descriptions_[description->name()].emplace_back(context().getCurrentDescriptionSourceName(),
                                                               std::move(description));
}

void lang::UnorderedScope::addEntity(lang::OwningHandle<lang::Entity> entity)
{
    assert(!defined_names_.contains(entity->name()) || defined_entities_.contains(entity->name()));

    defined_names_.emplace(entity->name());

    if (entity.handle().is<Function>())
    {
        lang::OwningHandle<lang::Function> function = lang::OwningHandle<lang::Function>::cast(std::move(entity));

        lang::ResolvingHandle<lang::FunctionGroup> group = prepareDefinedFunctionGroup(function->name());
        group->addFunction(std::move(function));
    }
    else
    {
        if (undefined_entities_.contains(entity->name()))
        {
            undefined_entities_.at(entity->name()).handle().reroute(entity.handle());
            undefined_entities_.erase(entity->name());
        }

        entity->setContainingScope(this);
        defined_entities_.emplace(entity->name(), std::move(entity));
    }
}

Optional<lang::ResolvingHandle<lang::Entity>> lang::UnorderedScope::getEntity(Identifier string)
{
    auto iterator = defined_entities_.find(string);

    if (iterator != defined_entities_.end())
    {
        auto& [name, type] = *iterator;
        return type.handle();
    }
    else return {};
}

void lang::UnorderedScope::onRegisterUsage(lang::ResolvingHandle<lang::Entity> entity)
{
    assert(!entity->isDefined());

    if (undefined_entities_.contains(entity->name()))
    {
        entity.reroute(undefined_entities_.at(entity->name()).handle());
        return;
    }

    if (defined_entities_.contains(entity->name()))
    {
        entity.reroute(defined_entities_.at(entity->name()).handle());
        return;
    }

    undefined_entities_.emplace(entity->name(), lang::OwningHandle<Entity>::takeOwnership(entity));
}

void lang::UnorderedScope::resolve()
{
    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        for (auto& description : descriptions) { description.description->initialize(*this); }
    }

    struct ResolvableID {
        ResolvableKind   kind;
        lang::Identifier name;

        std::weak_ordering operator<=>(ResolvableID const& other) const
        {
            if (kind != other.kind) return kind <=> other.kind;
            else return name <=> other.name;
        }
    };

    struct Resolvable {
        lang::Identifier                                       name;
        std::vector<std::reference_wrapper<lang::Description>> group;
    };

    lang::SortingGraph<ResolvableID, Resolvable> graph;
    std::map<lang::Identifier, ResolvableID>     declaration_providers;
    std::map<lang::Identifier, ResolvableID>     definition_providers;

    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        Resolvable resolvable = {name, {}};

        resolvable.group.reserve(descriptions.size());
        for (auto& description : descriptions) { resolvable.group.emplace_back(*description.description); }

        auto const& declaration = graph.addNode({ResolvableKind::DECLARATION, name}, resolvable);
        auto const& definition  = graph.addNode({ResolvableKind::DEFINITION, name}, resolvable);

        graph.addEdge(definition, declaration);

        assert(!descriptions.empty());

        if (descriptions.front().description->isOverloadAllowed())
        {
            declaration_providers.emplace(name, declaration);
            definition_providers.emplace(name, definition);
        }
        else
        {
            assert(descriptions.size() == 1);

            for (auto& provided : descriptions.front().description->getProvidedEntities())
            {
                declaration_providers.emplace(provided.get().name(), declaration);
                definition_providers.emplace(provided.get().name(), definition);
            }
        }
    }

    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        const ResolvableID     declaration = {ResolvableKind::DECLARATION, name};
        std::set<ResolvableID> declaration_dependencies;

        for (auto& description : descriptions)
        {
            for (auto& [dependency, depends_on_definition] : description.description->getDeclarationDependencies())
            {
                if (dependency.get().isDefined()) continue;

                if (depends_on_definition)
                {
                    if (definition_providers.contains(dependency.get().name()))
                    {
                        declaration_dependencies.emplace(definition_providers.at(dependency.get().name()));
                    }
                    else { missing_definitions_.push_back(dependency.get().name()); }
                }
                else
                {
                    if (declaration_providers.contains(dependency.get().name()))
                    {
                        declaration_dependencies.emplace(declaration_providers.at(dependency.get().name()));
                    }
                    else { missing_declarations_.push_back(dependency.get().name()); }
                }
            }
        }

        for (auto& dependency : declaration_dependencies) { graph.addEdge(declaration, dependency); }

        const ResolvableID     definition = {ResolvableKind::DEFINITION, name};
        std::set<ResolvableID> definition_dependencies;

        for (auto& description : descriptions)
        {
            for (auto& [dependency, depends_on_definition] : description.description->getDefinitionDependencies())
            {
                if (dependency.get().isDefined()) continue;

                if (depends_on_definition)
                {
                    if (definition_providers.contains(dependency.get().name()))
                    {
                        definition_dependencies.emplace(definition_providers.at(dependency.get().name()));
                    }
                    else { missing_definitions_.push_back(dependency.get().name()); }
                }
                else
                {
                    if (declaration_providers.contains(dependency.get().name()))
                    {
                        definition_dependencies.emplace(declaration_providers.at(dependency.get().name()));
                    }
                    else { missing_declarations_.push_back(dependency.get().name()); }
                }
            }
        }

        for (auto& dependency : definition_dependencies) { graph.addEdge(definition, dependency); }
    }

    if (!missing_declarations_.empty()) return;

    std::vector<ResolvableID> const order =
        graph.sort([&](ResolvableID const& cycle) { cyclic_definitions_.push_back(cycle.name); });

    if (!cyclic_definitions_.empty()) return;

    std::vector<ResolvableGroup> description_order;

    for (auto& id : order)
    {
        auto& resolvable = graph[id];

        if (id.kind == ResolvableKind::DECLARATION)
        {
            for (auto& description : resolvable.group) { description.get().resolveDeclaration(); }
        }

        if (id.kind == ResolvableKind::DEFINITION)
        {
            for (auto& description : resolvable.group) { description.get().resolveDefinition(); }
        }

        description_order.push_back({.descriptions = std::move(resolvable.group), .kind = id.kind});
    }

    description_order_ = std::move(description_order);

    if (scope() != this)
    {
        auto iterator = undefined_entities_.begin();

        while (iterator != undefined_entities_.end())
        {
            auto& [name, entity] = *iterator;

            if (scope()->resolveDefinition(entity.handle())) { iterator = undefined_entities_.erase(iterator); }
            else { ++iterator; }
        }
    }

    onResolve();
}

void lang::UnorderedScope::postResolve()
{
    for (auto& [name, entity] : defined_entities_)
    {
        auto type = entity.handle().as<Type>();
        if (type.hasValue()) (**type).postResolve();
    }

    onPostResolve();

    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        for (auto& description : descriptions) { description.description->postResolve(); }
    }

    Scope::postResolve();
}

bool lang::UnorderedScope::resolveDefinition(lang::ResolvingHandle<lang::Entity> entity)
{
    if (defined_entities_.contains(entity->name()))
    {
        entity.reroute(defined_entities_.at(entity->name()).handle());
        return true;
    }

    lang::Scope* parent = scope();

    if (parent != this) return parent->resolveDefinition(entity);

    return false;
}

void lang::UnorderedScope::validate(ValidationLogger& validation_logger) const
{
    for (auto const& [name, associated_descriptions] : incompatible_descriptions_)
    {
        bool              first_source = true;
        std::stringstream source_list;
        size_t            conflicting_imports = 0;

        std::vector<lang::Identifier> internal_conflicts;

        for (auto const& [source, description] : associated_descriptions)
        {
            if (source.hasValue())
            {
                if (first_source) first_source = false;
                else source_list << ", ";

                source_list << "'";
                source_list << source.value();
                source_list << "'";

                conflicting_imports++;
            }
            else { internal_conflicts.emplace_back(description->name()); }
        }

        assert(conflicting_imports + internal_conflicts.size() > 1);

        if (conflicting_imports > 1)
        {
            validation_logger.logError("Multiple definitions with the name '" + name
                                           + "' are imported from: " + source_list.str(),
                                       lang::Location::global());
        }

        for (auto const& internal_conflict : internal_conflicts)
        {
            if (conflicting_imports == 0)
            {
                validation_logger.logError("Multiple definitions with the name '" + name
                                               + "' are defined in the same scope",
                                           internal_conflict.location());
            }
            else
            {
                validation_logger.logError("Multiple definitions with the name '" + name
                                               + "' are defined in the same scope and imported from: "
                                               + source_list.str(),
                                           internal_conflict.location());
            }
        }
    }

    for (auto& name : missing_declarations_)
    {
        validation_logger.logError("No declaration for '" + name + "' found", name.location());
    }

    if (!missing_declarations_.empty()) return;

    for (auto& name : missing_definitions_)
    {
        validation_logger.logError("No definition for '" + name + "' found", name.location());
    }

    if (!missing_definitions_.empty()) return;

    for (auto& name : cyclic_definitions_)
    {
        validation_logger.logError("Name '" + name + "' part of cyclic dependency", name.location());
    }

    if (!cyclic_definitions_.empty()) return;

    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        for (auto& description : descriptions)
        {
            bool missing_dependencies = false;

            for (auto& declaration_dependency : description.description->getDeclarationDependencies())
            {
                Entity const& entity = declaration_dependency.entity.get();

                if (!entity.isDefined())
                {
                    validation_logger.logError("Name " + entity.getAnnotatedName() + " is undefined in current context",
                                               entity.name().location());
                    missing_dependencies = true;
                }
            }

            for (auto& definition_dependency : description.description->getDefinitionDependencies())
            {
                Entity const& entity = definition_dependency.entity.get();

                if (!entity.isDefined())
                {
                    validation_logger.logError("Name " + entity.getAnnotatedName() + " is undefined in current context",
                                               entity.name().location());
                    missing_dependencies = true;
                }
            }

            if (missing_dependencies) continue;
            if (description.description->isImported()) continue;

            description.description->validate(validation_logger);
        }
    }

    for (auto& [name, entity] : defined_entities_)
    {
        auto const* function_group = entity.handle().get().as<FunctionGroup>();
        if (function_group != nullptr) function_group->validate(validation_logger);
    }

    auto& defined_entities = const_cast<UnorderedScope*>(this)->defined_entities_;

    std::vector<lang::ResolvingHandle<lang::Variable>> global_variables;
    for (auto& [name, entity] : defined_entities)
    {
        Optional<lang::ResolvingHandle<lang::Variable>> variable = entity.handle().as<lang::Variable>();
        if (variable.hasValue()) global_variables.emplace_back(variable.value());
    }
}

void lang::UnorderedScope::buildDeclarations(CompileContext& context)
{
    for (auto& [name, entity] : defined_entities_)
    {
        if (auto type = castToType<lang::Type>(entity); type.hasValue() and not(**type).isCustom())
        {
            (**type).buildNativeDeclaration(context);
        }
    }

    for (auto& group : description_order_.value())
    {
        if (group.kind == ResolvableKind::DEFINITION) continue;

        for (auto& description : group.descriptions) { description.get().buildDeclaration(context); }
    }
}

void lang::UnorderedScope::buildDefinitions(CompileContext& context)
{
    for (auto& [name, entity] : defined_entities_)
    {
        if (auto type = castToType<lang::Type>(entity); type.hasValue() and not(**type).isCustom())
        {
            (**type).buildNativeDefinition(context);
        }
    }

    for (auto& group : description_order_.value())
    {
        if (group.kind == ResolvableKind::DEFINITION) continue;

        for (auto& description : group.descriptions) { description.get().buildDefinition(context); }
    }
}

void lang::UnorderedScope::buildInitialization(CompileContext& context)
{
    for (auto& group : description_order_.value())
    {
        if (group.kind == ResolvableKind::DEFINITION) continue;

        for (auto& description : group.descriptions) { description.get().buildInitialization(context); }
    }
}

void lang::UnorderedScope::buildFinalization(CompileContext& context)
{
    for (auto& group : description_order_.value())
    {
        if (group.kind == ResolvableKind::DEFINITION) continue;

        for (auto& description : group.descriptions) { description.get().buildFinalization(context); }
    }
}

std::map<lang::Identifier, std::vector<lang::UnorderedScope::AssociatedDescription>>& lang::UnorderedScope::
    getCompatibleDescriptions()
{
    return compatible_descriptions_;
}

std::map<lang::Identifier, std::vector<lang::UnorderedScope::AssociatedDescription>> const& lang::UnorderedScope::
    getCompatibleDescriptions() const
{
    return compatible_descriptions_;
}

lang::ResolvingHandle<lang::FunctionGroup> lang::UnorderedScope::prepareDefinedFunctionGroup(Identifier name)
{
    if (defined_entities_.contains(name))
    {
        auto function_group = defined_entities_.at(name).handle().as<FunctionGroup>();
        if (function_group.hasValue()) return function_group.value();

        throw std::logic_error("Entity with name '" + name + "' is not a function group.");
    }

    lang::OwningHandle<lang::FunctionGroup> function_group =
        lang::OwningHandle<lang::FunctionGroup>::takeOwnership(lang::makeHandled<lang::FunctionGroup>(name));

    if (undefined_entities_.contains(name))
    {
        undefined_entities_.at(name).handle().reroute(function_group.handle());
        undefined_entities_.erase(name);
    }

    lang::ResolvingHandle<lang::FunctionGroup> handle = function_group.handle();
    defined_entities_.emplace(name, std::move(function_group));

    handle->setScope(*this);

    return handle;
}

template<typename Target>
static std::vector<lang::ResolvingHandle<Target>> getHandles(
    std::map<lang::Identifier, lang::OwningHandle<lang::Entity>>& entities)
{
    std::vector<lang::ResolvingHandle<Target>> result;
    for (auto& [name, entity] : entities)
    {
        auto target = entity.handle().as<Target>();
        if (target.hasValue()) result.emplace_back(target.value());
    }

    return result;
}

template<typename Target>
static std::vector<std::reference_wrapper<Target const>> getReferences(
    std::map<lang::Identifier, lang::OwningHandle<lang::Entity>> const& entities)
{
    std::vector<std::reference_wrapper<Target const>> result;
    for (auto& [name, entity] : entities)
    {
        auto target = entity.handle().get().as<Target>();
        if (target != nullptr) result.emplace_back(*target);
    }

    return result;
}

std::vector<lang::ResolvingHandle<lang::FunctionGroup>> lang::UnorderedScope::getFunctionGroups()
{
    return getHandles<FunctionGroup>(defined_entities_);
}

std::vector<std::reference_wrapper<const lang::FunctionGroup>> lang::UnorderedScope::getFunctionGroups() const
{
    return getReferences<FunctionGroup>(defined_entities_);
}

std::vector<lang::ResolvingHandle<lang::Variable>> lang::UnorderedScope::getVariables()
{
    return getHandles<Variable>(defined_entities_);
}

std::vector<std::reference_wrapper<const lang::Variable>> lang::UnorderedScope::getVariables() const
{
    return getReferences<Variable>(defined_entities_);
}

std::vector<lang::ResolvingHandle<lang::Type>> lang::UnorderedScope::getTypes()
{
    return getHandles<Type>(defined_entities_);
}

std::vector<std::reference_wrapper<const lang::Type>> lang::UnorderedScope::getTypes() const
{
    return getReferences<Type>(defined_entities_);
}
