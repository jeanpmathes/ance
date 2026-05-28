#include "Memory.h"

#include <ranges>

#include "ance/bbt/Value.h"

ance::utility::Optional<ance::utility::Shared<ance::bbt::Value>> ance::cet::Memory::readAt(utility::Shared<bbt::Value>   value,
                                                                                           std::span<size_t const> const indices,
                                                                                           bbt::TypeContext&             type_context)
{
    for (size_t const index : indices)
    {
        utility::Optional<utility::Shared<bbt::Value>> accessed = value->access(index, nullptr, type_context);

        if (accessed.hasValue())
        {
            value = accessed.value();
        }
        else return std::nullopt;
    }

    return value;
}

ance::utility::Optional<ance::utility::Shared<ance::bbt::Value>> ance::cet::Memory::writeAt(utility::Shared<bbt::Value>   value,
                                                                                            std::span<size_t const> const indices,
                                                                                            utility::Shared<bbt::Value>   replacement,
                                                                                            bbt::TypeContext&             type_context)
{
    utility::List<std::pair<utility::Shared<bbt::Value>, size_t>> path;
    path.reserve(indices.size());

    for (size_t const index : indices)
    {
        path.emplace_back(value, index);

        if (path.size() == indices.size())
        {
            // No need to load the innermost value, we are going to replace it anyway.

            break;
        }

        utility::Optional<utility::Shared<bbt::Value>> accessed = value->access(index, nullptr, type_context);

        if (accessed.hasValue())
        {
            value = accessed.value();
        }
        else return std::nullopt;
    }

    for (auto& [target, index] : path | std::views::reverse)
    {
        utility::Optional<utility::Shared<bbt::Value>> accessed = target->access(index, &replacement, type_context);

        if (accessed.hasValue())
        {
            replacement = accessed.value();
        }
        else return std::nullopt;
    }

    return replacement;
}
