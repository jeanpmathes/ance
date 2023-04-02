#include "Identifier.h"

#include <iostream>

#include "lang/utility/Storage.h"
#include "lang/utility/StringStorage.h"

lang::Identifier::Identifier(std::string_view string, lang::Location location) : string_(string), location_(location) {}

lang::Identifier lang::Identifier::like(std::string const& string, lang::Location location)
{
    std::string_view const view = lang::StringStorage::shared().store(string);

    return {view, location};
}

lang::Identifier lang::Identifier::empty()
{
    return {std::string_view(), lang::Location::global()};
}

std::string_view lang::Identifier::text() const
{
    return string_;
}

lang::Location lang::Identifier::location() const
{
    return location_;
}

void lang::Identifier::synchronize(lang::Identifier* identifier, Storage& storage)
{
    std::string content;

    if (storage.isWriting()) { content = std::string(identifier->string_); }

    storage.sync(content);

    if (storage.isReading()) { *identifier = like(content, identifier->location_); }
}

std::ostream& operator<<(std::ostream& os, lang::Identifier const& identifier)
{
    os << identifier.text();
    return os;
}

std::string operator+(std::string const& str, lang::Identifier const& identifier)
{
    return str + std::string(identifier.text());
}

std::string operator+(lang::Identifier const& identifier, std::string const& str)
{
    return std::string(identifier.text()) + str;
}

std::string operator+(char const* str, lang::Identifier const& identifier)
{
    return str + std::string(identifier.text());
}

std::string operator+(lang::Identifier const& identifier, char const* str)
{
    return std::string(identifier.text()) + str;
}
