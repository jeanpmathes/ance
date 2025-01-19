#include "StringStorage.h"

ance::core::StringStorage& ance::core::StringStorage::shared()
{
    static StringStorage storage;
    return storage;
}

std::string_view ance::core::StringStorage::store(std::string const& string)
{
    std::string_view view;

    if (auto const it = storage_.find(string); it != storage_.end()) { view = *it; }
    else
    {
        auto [new_it, success] = storage_.emplace(string);
        view                   = *new_it;
    }

    return view;
}
