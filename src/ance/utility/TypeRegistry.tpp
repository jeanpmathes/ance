#include "TypeRegistry.h"

template<typename OTHER_KEY>
std::optional<TypeHandle> ance::TypeRegistry<OTHER_KEY>::get(const UsedTypes& type_keys, const OTHER_KEY& other_keys) const
{
    for (auto& [current_key, current_type] : types_)
    {
        auto& [current_type_keys, current_other_key] = current_key;

        if (current_type_keys == type_keys && current_other_key == other_keys)
        {
            return current_type;
        }
    }

    return {};
}

template<typename OTHER_KEY>
void ance::TypeRegistry<OTHER_KEY>::add(UsedTypes&& type_keys, OTHER_KEY other_key, TypeHandle type)
{
    types_.emplace_back(std::make_pair(std::make_pair(std::move(type_keys), other_key), type));
}

template<typename OTHER_KEY>
void ance::TypeRegistry<OTHER_KEY>::resolve()
{
    for (auto& [key, type] : types_)
    {
        auto& [type_keys, other_key] = key;

        for (auto& used_type : type_keys)
        {
            type->scope().resolve(used_type);
        }
    }
}
