#include "Identifier.h"

#include <iostream>

#include "StringStorage.h"

ance::core::Identifier::Identifier(std::string_view const string, Location const& location) : string_(string), location_(location) {}

ance::core::Identifier ance::core::Identifier::like(std::string const& string, Location location)
{
    std::string_view const view = StringStorage::shared().store(string);

    return {view, location};
}

ance::core::Identifier ance::core::Identifier::from(Location location)
{
    if (location.isGlobal())
        throw std::invalid_argument("Cannot create an identifier from a global location");

    std::string const text = std::format("/* tmp-var \"{}:{}:{}\" */", location.file(), location.line(), location.column());
    std::string_view const view = StringStorage::shared().store(text);

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

std::ostream& operator<<(std::ostream& os, ance::core::Identifier const& identifier)
{
    os << identifier.text();
    return os;
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
