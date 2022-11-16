#include "DictionaryElement.h"

std::optional<std::reference_wrapper<const data::Element>> data::DictionaryElement::operator[](
    std::string const& key) const
{
    if (dict_.find(key) != dict_.end())
    {
        std::unique_ptr<data::Element> const& ptr = dict_.at(key);
        return *ptr;
    }
    else { return {}; }
}

void data::DictionaryElement::put(std::string const& key, std::unique_ptr<data::Element> element)
{
    dict_.insert({key, std::move(element)});
}
