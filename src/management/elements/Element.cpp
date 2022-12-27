#include "Element.h"

Optional<std::reference_wrapper<const data::Element>> data::Element::operator[](std::string const&) const
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

Optional<std::reference_wrapper<const std::string>> data::Element::asString() const
{
    return {};
}

Optional<bool> data::Element::asBool() const
{
    return {};
}

data::Element::~Element() {}
