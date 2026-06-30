#include "Memory.h"

#include <ranges>

#include "ance/bbt/Value.h"

ance::utility::Optional<ance::utility::Shared<ance::bbt::Value const>> ance::cet::Memory::load(utility::Shared<bbt::Value const> value,
                                                                                               std::span<size_t const> const indices,
                                                                                           bbt::TypeContext&             type_context)
{
    for (size_t const index : indices)
    {
        utility::Optional<utility::Shared<bbt::Value const>> accessed = value->access(index, nullptr, type_context);

        if (accessed.hasValue())
        {
            value = accessed.value();
        }
        else return std::nullopt;
    }

    return value;
}

ance::utility::Optional<ance::utility::Shared<ance::bbt::Value const>> ance::cet::Memory::store(utility::Shared<bbt::Value const> value,
                                                                                                std::span<size_t const> const indices,
                                                                                                utility::Shared<bbt::Value const> replacement,
                                                                                                bbt::TypeContext&             type_context)
{
    utility::List<std::pair<utility::Shared<bbt::Value const>, size_t>> path;
    path.reserve(indices.size());

    for (size_t const index : indices)
    {
        path.emplace_back(value, index);

        if (path.size() == indices.size())
        {
            // No need to load the innermost value, we are going to replace it anyway.

            break;
        }

        utility::Optional<utility::Shared<bbt::Value const>> accessed = value->access(index, nullptr, type_context);

        if (accessed.hasValue())
        {
            value = accessed.value();
        }
        else return std::nullopt;
    }

    for (auto& [target, index] : path | std::views::reverse)
    {
        utility::Optional<utility::Shared<bbt::Value const>> accessed = target->access(index, &replacement, type_context);

        if (accessed.hasValue())
        {
            replacement = accessed.value();
        }
        else return std::nullopt;
    }

    return replacement;
}
