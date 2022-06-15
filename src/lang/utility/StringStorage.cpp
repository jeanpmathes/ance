#include "StringStorage.h"

lang::StringStorage& lang::StringStorage::shared()
{
    static StringStorage storage;
    return storage;
}

std::string_view lang::StringStorage::store(const std::string& string)
{
    std::string_view view;

    auto it = storage_.find(string);

    if (it != storage_.end()) { view = *it; }
    else {
        auto [new_it, success] = storage_.emplace(string);
        view                   = *new_it;
    }

    return view;
}
