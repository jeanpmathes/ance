#include "Value.h"

#include <sstream>
#include <utility>

#include "ance/bbt/Type.h"

namespace ance::bbt
{
    Value::Value(utility::Optional<utility::Shared<Type>> type) : type_(std::move(type))
    {

    }

    utility::Shared<Type> Value::type()
    {
        return type_.valueOr(Type::Self());
    }

    Type const& Value::type() const
    {
        return type_.hasValue() ? *type_.value() : *Type::Self();
    }

    Unit::Unit() : Value(Type::Unit()) {}

    utility::Shared<Unit> Unit::make()
    {
        return utility::makeShared<Unit>();
    }

    std::string Unit::toString() const
    {
        return "()";
    }

    Bool::Bool(bool const value) : Value(Type::Bool()), value_(value) {}

    utility::Shared<Bool> Bool::make(bool const value)
    {
        return utility::makeShared<Bool>(value);
    }

    std::string Bool::toString() const
    {
        return value_ ? "true" : "false";
    }

    bool Bool::value() const
    {
        return value_;
    }

    Size::Size(size_t const value) : Value(Type::Size()), value_(value) {}

    utility::Shared<Size> Size::make(size_t value)
    {
        return utility::makeShared<Size>(value);
    }

    std::string Size::toString() const
    {
        return std::to_string(value_);
    }

    size_t Size::value() const
    {
        return value_;
    }

    Identifier::Identifier(core::Identifier const& identifier) : Value(Type::Ident()), identifier_(identifier) {}

    utility::Shared<Identifier> Identifier::make(core::Identifier const& identifier)
    {
        return utility::makeShared<Identifier>(identifier);
    }

    std::string Identifier::toString() const
    {
        return "#" + std::string(identifier_.text());
    }

    core::Identifier const& Identifier::value() const
    {
        return identifier_;
    }

    Location::Location(core::Location const& location) : Value(Type::Location()), location_(location) {}

    utility::Shared<Location> Location::make(core::Location const& location)
    {
        return utility::makeShared<Location>(location);
    }

    std::string Location::toString() const
    {
        std::stringstream ss;
        ss << location_;
        return ss.str();
    }

    core::Location const& Location::value() const
    {
        return location_;
    }

    String::String(std::string value) : Value(Type::String()), value_(std::move(value)) {}

    utility::Shared<String> String::make(std::string value)
    {
        return utility::makeShared<String>(std::move(value));
    }

    std::string String::toString() const
    {
        return value_;
    }

    std::string const& String::value() const
    {
        return value_;
    }
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Value const& value)
{
    return out << value.toString();
}
