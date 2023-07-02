#include "UnorderedScope.h"

#include <iostream>
#include <sstream>
#include <string>

#include "lang/ApplicationVisitor.h"
#include "lang/construct/descriptions/Description.h"
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

void lang::UnorderedScope::addFunction(lang::OwningHandle<lang::Function> function)
{
    assert(!defined_names_.contains(function->name()) || defined_function_groups_.contains(function->name()));

    defined_names_.emplace(function->name());

    lang::ResolvingHandle<lang::FunctionGroup> group = prepareDefinedFunctionGroup(function->name());
    group->addFunction(std::move(function));
}

void lang::UnorderedScope::addVariable(lang::OwningHandle<lang::Variable> variable)
{
    assert(!defined_names_.contains(variable->name()) || global_undefined_variables_.contains(variable->name()));

    defined_names_.emplace(variable->name());

    if (global_undefined_variables_.contains(variable->name()))
    {
        global_undefined_variables_.at(variable->name()).handle().reroute(variable.handle());
        global_undefined_variables_.erase(variable->name());
    }

    global_defined_variables_.emplace(variable->name(), std::move(variable));
}

void lang::UnorderedScope::addType(lang::OwningHandle<lang::Type> type)
{
    assert(!defined_names_.contains(type->name()) || undefined_types_.contains(type->name()));

    defined_names_.emplace(type->name());

    if (undefined_types_.contains(type->name()))
    {
        undefined_types_.at(type->name()).handle().reroute(type.handle());
        undefined_types_.erase(type->name());
    }

    type->setContainingScope(this);
    defined_types_.emplace(type->name(), std::move(type));
}

Optional<lang::ResolvingHandle<lang::Type>> lang::UnorderedScope::getType(Identifier string)
{
    auto it = defined_types_.find(string);

    if (it != defined_types_.end())
    {
        auto& [name, type] = *it;
        return type.handle();
    }
    else return {};
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

    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        for (auto& description : descriptions)
        {
            if (description.description->isImported()) continue;
            description.description->validate(validation_logger);
        }
    }

    for (auto& [key, function] : defined_function_groups_) { function->validate(validation_logger); }

    auto& global_defined_variables = const_cast<UnorderedScope*>(this)->global_defined_variables_;

    std::vector<lang::ResolvingHandle<lang::Variable>> global_variables;
    global_variables.reserve(global_defined_variables.size());
    for (auto& [name, variable] : global_defined_variables) { global_variables.emplace_back(variable.handle()); }

    lang::GlobalVariable::determineOrder(global_variables, &validation_logger);
}

template<typename E>
static void registerEntityUsage(lang::ResolvingHandle<E>                           entity,
                                std::map<lang::Identifier, lang::OwningHandle<E>>& undefined_entities,
                                std::map<lang::Identifier, lang::OwningHandle<E>>& defined_entities)
{
    assert(!entity->isDefined());

    if (undefined_entities.contains(entity->name()))
    {
        entity.reroute(undefined_entities.at(entity->name()).handle());
        return;
    }

    if (defined_entities.contains(entity->name()))
    {
        entity.reroute(defined_entities.at(entity->name()).handle());
        return;
    }

    undefined_entities.emplace(entity->name(), lang::OwningHandle<E>::takeOwnership(entity));
}

void lang::UnorderedScope::registerUsage(lang::ResolvingHandle<lang::Variable> variable)
{
    registerEntityUsage(variable, global_undefined_variables_, global_defined_variables_);
}

void lang::UnorderedScope::registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function_group)
{
    registerEntityUsage(function_group, undefined_function_groups_, defined_function_groups_);
}

void lang::UnorderedScope::registerUsage(lang::ResolvingHandle<lang::Type> type)
{
    registerEntityUsage(type, undefined_types_, defined_types_);
}

void lang::UnorderedScope::registerDefinition(lang::ResolvingHandle<lang::Type> type)
{
    assert(type->isDefined());
    assert(not defined_types_.contains(type->name()));

    defined_types_.emplace(type->name(), lang::OwningHandle<lang::Type>::takeOwnership(type));
    type->setContainingScope(this);

    if (undefined_types_.contains(type->name()))
    {
        lang::OwningHandle<lang::Type> undefined = std::move(undefined_types_.at(type->name()));
        undefined_types_.erase(type->name());

        undefined.handle().reroute(type);
    }
}

void lang::UnorderedScope::resolve()
{
    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        for (auto& description : descriptions) { description.description->initialize(*this); }
    }

    for (auto& [key, group] : defined_function_groups_) { group->resolve(); }

    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        for (auto& description : descriptions) { description.description->resolve(); }
    }

    onResolve();
}

void lang::UnorderedScope::postResolve()
{
    for (auto& [name, type] : defined_types_) { type->postResolve(); }

    onPostResolve();

    for (auto& [key, group] : defined_function_groups_) { group->postResolve(); }

    for (auto& [name, descriptions] : compatible_descriptions_)
    {
        for (auto& description : descriptions) { description.description->postResolve(); }
    }
}

template<typename E>
static bool resolveEntityDefinition(lang::ResolvingHandle<E>                           entity,
                                    std::map<lang::Identifier, lang::OwningHandle<E>>& defined_entities)
{
    if (defined_entities.contains(entity->name()))
    {
        entity.reroute(defined_entities.at(entity->name()).handle());
        return true;
    }

    return false;
}

bool lang::UnorderedScope::resolveDefinition(lang::ResolvingHandle<lang::Variable> variable)
{
    return resolveEntityDefinition(variable, global_defined_variables_);
}

bool lang::UnorderedScope::resolveDefinition(lang::ResolvingHandle<lang::FunctionGroup> function_group)
{
    return resolveEntityDefinition(function_group, defined_function_groups_);
}

bool lang::UnorderedScope::resolveDefinition(lang::ResolvingHandle<lang::Type> type)
{
    return resolveEntityDefinition(type, defined_types_);
}

void lang::UnorderedScope::buildInitialization(CompileContext& context)
{
    std::vector<lang::ResolvingHandle<lang::Variable>> global_variables;
    global_variables.reserve(global_defined_variables_.size());
    for (auto& [name, variable] : global_defined_variables_) { global_variables.emplace_back(variable.handle()); }

    global_variables = GlobalVariable::determineOrder(global_variables, nullptr);

    for (auto& variable : global_variables) { variable->buildDefinition(context); }
}

void lang::UnorderedScope::buildFinalization(CompileContext& context)
{
    for (auto& [name, variable] : global_defined_variables_) { variable->buildFinalization(context); }
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
    if (defined_function_groups_.find(name) != defined_function_groups_.end())
    {
        return defined_function_groups_.at(name).handle();
    }

    Optional<lang::OwningHandle<lang::FunctionGroup>> undefined;

    if (undefined_function_groups_.contains(name))
    {
        undefined = std::move(undefined_function_groups_.at(name));
        undefined_function_groups_.erase(name);
    }
    else
    {
        undefined =
            lang::OwningHandle<lang::FunctionGroup>::takeOwnership(lang::makeHandled<lang::FunctionGroup>(name));
    }

    lang::ResolvingHandle<lang::FunctionGroup> defined = undefined->handle();
    defined_function_groups_.emplace(name, std::move(undefined.value()));

    return defined;
}
