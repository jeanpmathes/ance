#include "ListElement.h"

std::vector<std::reference_wrapper<const data::Element>>::const_iterator data::ListElement::begin() const
{
    return const_list_.begin();
}

std::vector<std::reference_wrapper<const data::Element>>::const_iterator data::ListElement::end() const
{
    return const_list_.end();
}

void data::ListElement::put(std::unique_ptr<data::Element> element)
{
    const_list_.emplace_back(*element);
    list_.push_back(std::move(element));
}
