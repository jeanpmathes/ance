#include "DictionaryElement.h"

Optional<std::reference_wrapper<const data::Element>> data::DictionaryElement::operator[](std::string const& key) const
{
    if (dict_.find(key) != dict_.end())
    {
        std::unique_ptr<data::Element> const& ptr = dict_.at(key);
        return std::cref(*ptr);
    }
    else { return {}; }
}

void data::DictionaryElement::put(std::string const& key, std::unique_ptr<data::Element> element)
{
    dict_.insert({key, std::move(element)});
}
