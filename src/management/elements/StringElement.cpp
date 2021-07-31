#include "StringElement.h"

#include <utility>

data::StringElement::StringElement(std::string string) : string_(std::move(string)) {}

std::optional<std::reference_wrapper<const std::string>> data::StringElement::asString() const
{
    return string_;
}
