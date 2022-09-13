#include "Element.h"

std::optional<std::reference_wrapper<const data::Element>> data::Element::operator[](const std::string&) const
{
    return {};
}

std::vector<std::reference_wrapper<const data::Element>>::const_iterator data::Element::begin() const
{
    return empty_vector_.cend();
}

std::vector<std::reference_wrapper<const data::Element>>::const_iterator data::Element::end() const
{
    return empty_vector_.cend();
}

std::optional<std::reference_wrapper<const std::string>> data::Element::asString() const
{
    return {};
}

std::optional<bool> data::Element::asBool() const
{
    return {};
}

data::Element::~Element() {}

