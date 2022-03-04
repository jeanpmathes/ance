#include "TypeRegistry.h"

template<typename OTHER_KEY>
std::optional<TypeHandle> lang::TypeRegistry<OTHER_KEY>::get(const UsedTypes& type_keys,
                                                             const OTHER_KEY& other_keys) const
{
    for (auto& [current_key, current_type] : types_)
    {
        auto& [current_type_keys, current_other_key] = current_key;

        if (current_type_keys == type_keys && current_other_key == other_keys) { return current_type; }
    }

    return {};
}

template<typename OTHER_KEY>
void lang::TypeRegistry<OTHER_KEY>::add(UsedTypes&& type_keys, OTHER_KEY other_key, TypeHandle type)
{
    types_.emplace_back(std::make_pair(std::make_pair(std::move(type_keys), other_key), type));
}

template<typename OTHER_KEY>
void lang::TypeRegistry<OTHER_KEY>::setDefaultContainingScope(lang::Scope* scope)
{
    for (auto& [key, type] : types_)
    {
        if (type->isCustom()) continue;
        type->setContainingScope(scope);
    }
}

template<typename OTHER_KEY>
void lang::TypeRegistry<OTHER_KEY>::resolve()
{
    for (auto& [key, type] : types_)
    {
        auto& [type_keys, other_key] = key;

        for (auto& used_type : type_keys)
        {
            if (used_type->isDefined()) continue;
            type->getContainingScope()->resolveDefinition(used_type);
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