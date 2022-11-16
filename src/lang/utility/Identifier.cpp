#include "Identifier.h"

#include "lang/utility/StringStorage.h"

lang::Identifier::Identifier(std::string_view string, lang::Location location) : string_(string), location_(location) {}

lang::Identifier lang::Identifier::from(std::string const& string, lang::Location location)
{
    std::string_view view = lang::StringStorage::shared().store(string);

    return {view, location};
}

std::string_view lang::Identifier::text() const
{
    return string_;
}

lang::Location lang::Identifier::location() const
{
    return location_;
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
