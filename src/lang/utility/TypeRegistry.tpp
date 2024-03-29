#include "TypeRegistry.h"

template<typename OtherKey>
Optional<TypeHandle> lang::TypeRegistry<OtherKey>::get(UsedTypes type_keys, OtherKey other_keys)
{
    for (auto& [current_key, current_type] : types_)
    {
        auto& [current_type_keys, current_other_key] = current_key;

        if (current_type_keys == type_keys && current_other_key == other_keys) { return current_type; }
    }

    return {};
}

template<typename OtherKey>
void lang::TypeRegistry<OtherKey>::add(UsedTypes&& type_keys, OtherKey other_key, TypeHandle type)
{
    types_.emplace_back(std::make_pair(std::make_pair(std::move(type_keys), other_key), type));

    if (scope_ && not type->isCustom()) { type->setContainingScope(scope_); }
}

template<typename OtherKey>
void lang::TypeRegistry<OtherKey>::setDefaultContainingScope(lang::Scope& scope)
{
    scope_ = &scope;

    for (auto& [key, type] : types_)
    {
        if (type->isCustom()) continue;
        type->setContainingScope(&scope);
    }
}

template<typename OtherKey>
void lang::TypeRegistry<OtherKey>::resolve()
{
    for (auto& [key, type] : types_)
    {
        auto& [type_keys, other_key] = key;

        for (auto& used_type : type_keys)
        {
            if (used_type->isDefined()) continue;
            type->scope().resolveDefinition(used_type);
        }
    }

    std::vector<Entry> merged;

    for (auto& [current_key, current_type] : types_)
    {
        auto& [current_type_keys, current_other_key] = current_key;

        bool was_merged = false;

        for (auto& [merged_key, merged_type] : merged)
        {
            auto& [merged_type_keys, merged_other_key] = merged_key;

            if (merged_type_keys == current_type_keys && merged_other_key == current_other_key)
            {
                was_merged = true;
                current_type.reroute(merged_type);
                break;
            }
        }

        if (!was_merged)
        {
            merged.emplace_back(std::make_pair(std::move(current_type_keys), std::move(current_other_key)),
                                std::move(current_type));
        }
    }

    types_ = std::move(merged);
}

template<typename OtherKey>
void lang::TypeRegistry<OtherKey>::clear()
{
    types_.clear();
}

template<typename OtherKey>
void lang::TypeRegistry<OtherKey>::postResolve()
{
    for (size_t index = 0; index < types_.size(); ++index)// Allows adding types during iteration.
    {
        auto& [key, type] = types_[index];
        if (type->isDefined()) type->postResolve();
    }
}

template<typename OtherKey>
void lang::TypeRegistry<OtherKey>::registerDeclarations(Execution& exec)
{
    for (size_t index = 0; index < types_.size(); ++index)// Allows adding types during iteration.
    {
        auto& [key, type] = types_[index];
        type->registerDeclaration(exec);
    }
}

template<typename OtherKey>
void lang::TypeRegistry<OtherKey>::registerDefinitions(Execution& exec)
{
    for (size_t index = 0; index < types_.size(); ++index)// Allows adding types during iteration.
    {
        auto& [key, type] = types_[index];
        type->registerDefinition(exec);
    }
}
