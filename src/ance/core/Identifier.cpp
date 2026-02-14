#include "Identifier.h"

#include <iostream>

#include "StringStorage.h"

ance::core::Identifier::Identifier(std::string_view const string, Location const& location) : string_(string), location_(location) {}

ance::core::Identifier ance::core::Identifier::make(std::string const& string, Location location)
{
    std::string_view const view = StringStorage::shared().store(string);

    return {view, location};
}

ance::core::Identifier ance::core::Identifier::empty()
{
    return {std::string_view(), Location::global()};
}

std::string_view ance::core::Identifier::text() const
{
    return string_;
}

ance::core::Location ance::core::Identifier::location() const
{
    return location_;
}

bool ance::core::Identifier::isEmpty() const
{
    return string_.empty();
}

std::weak_ordering ance::core::Identifier::operator<=>(Identifier const& other) const
{
    return string_ <=> other.string_;
}

std::string operator+(std::string const& str, ance::core::Identifier const& identifier)
{
    return str + std::string(identifier.text());
}

std::string operator+(ance::core::Identifier const& identifier, std::string const& str)
{
    return std::string(identifier.text()) + str;
}

std::string operator+(char const* str, ance::core::Identifier const& identifier)
{
    return str + std::string(identifier.text());
}

std::string operator+(ance::core::Identifier const& identifier, char const* str)
{
    return std::string(identifier.text()) + str;
}

std::ostream& ance::core::operator<<(std::ostream& os, Identifier const& identifier)
{
    return os << identifier.text();
}
