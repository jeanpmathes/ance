#include "Identifier.h"

#include <utility>

lang::Identifier::Identifier(std::string string, lang::Location location)
    : string_(std::move(string))
    , location_(location)
{}

lang::Identifier lang::Identifier::from(const std::string& string, lang::Location location)
{
    return {std::string(string), location};
}

std::string_view lang::Identifier::text() const
{
    return string_;
}

lang::Location lang::Identifier::location() const
{
    return location_;
}

std::ostream& operator<<(std::ostream& os, const lang::Identifier& identifier)
{
    os << identifier.text();
    return os;
}

std::string operator+(const std::string& str, const lang::Identifier& identifier)
{
    return str + std::string(identifier.text());
}

std::string operator+(const lang::Identifier& identifier, const std::string& str)
{
    return std::string(identifier.text()) + str;
}

std::string operator+(const char* str, const lang::Identifier& identifier)
{
    return str + std::string(identifier.text());
}

std::string operator+(const lang::Identifier& identifier, const char* str)
{
    return std::string(identifier.text()) + str;
}
