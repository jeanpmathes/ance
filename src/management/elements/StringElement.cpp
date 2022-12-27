#include "StringElement.h"

#include <utility>

data::StringElement::StringElement(std::string string) : string_(std::move(string)) {}

Optional<std::reference_wrapper<const std::string>> data::StringElement::asString() const
{
    return std::cref(string_);
}
