#include "DictionaryElement.h"

std::optional<std::reference_wrapper<const data::Element>> data::DictionaryElement::operator[](
    const std::string& key) const
{
    if (dict_.find(key) != dict_.end())
    {
        const std::unique_ptr<data::Element>& ptr = dict_.at(key);
        return *ptr;
    }
    else
    {
        return {};
    }
}

void data::DictionaryElement::put(const std::string& key, std::unique_ptr<data::Element> element)
{
    dict_.insert({key, std::move(element)});
}
