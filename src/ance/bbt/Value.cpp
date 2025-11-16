#include "Value.h"

#include <sstream>
#include <utility>

#include "ance/core/Type.h"

namespace ance::bbt
{
    Value::Value(core::Type const& type) : type_(type)
    {

    }

    core::Type const& Value::type() const
    {
        return type_;
    }

    Unit::Unit() : Value(core::Type::Unit()) {}

    utility::Shared<Unit> Unit::make()
    {
        return utility::makeShared<Unit>();
    }

    std::string Unit::toString() const
    {
        return "()";
    }

    utility::Shared<Value> Unit::clone() const
    {
        return make();
    }

    Bool::Bool(bool const value) : Value(core::Type::Bool()), value_(value) {}

    utility::Shared<Bool> Bool::make(bool const value)
    {
        return utility::makeShared<Bool>(value);
    }

    std::string Bool::toString() const
    {
        return value_ ? "true" : "false";
    }

    utility::Shared<Value> Bool::clone() const
    {
        return make(value_);
    }

    bool Bool::value() const
    {
        return value_;
    }

    Size::Size(size_t const value) : Value(core::Type::Size()), value_(value) {}

    utility::Shared<Size> Size::make(size_t value)
    {
        return utility::makeShared<Size>(value);
    }

    std::string Size::toString() const
    {
        return std::to_string(value_);
    }

    utility::Shared<Value> Size::clone() const
    {
        return make(value_);
    }

    size_t Size::value() const
    {
        return value_;
    }

    Identifier::Identifier(core::Identifier const& identifier) : Value(core::Type::Ident()), identifier_(identifier) {}

    utility::Shared<Identifier> Identifier::make(core::Identifier const& identifier)
    {
        return utility::makeShared<Identifier>(identifier);
    }

    std::string Identifier::toString() const
    {
        return "#" + std::string(identifier_.text());
    }

    utility::Shared<Value> Identifier::clone() const
    {
        return make(identifier_);
    }

    core::Identifier const& Identifier::value() const
    {
        return identifier_;
    }

    Type::Type(core::Type const& type) : Value(core::Type::Self()), type_(type) {}

    utility::Shared<Type> Type::make(core::Type const& type)
    {
        return utility::makeShared<Type>(type);
    }

    std::string Type::toString() const
    {
        return std::string(type_.name().text());
    }

    utility::Shared<Value> Type::clone() const
    {
        return make(type_);
    }

    core::Type const& Type::value() const
    {
        return type_;
    }

    Location::Location(core::Location const& location) : Value(core::Type::Location()), location_(location) {}

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

    utility::Shared<Value> Location::clone() const
    {
        return make(location_);
    }

    core::Location const& Location::value() const
    {
        return location_;
    }

    String::String(std::string value) : Value(core::Type::String()), value_(std::move(value)) {}

    utility::Shared<String> String::make(std::string value)
    {
        return utility::makeShared<String>(std::move(value));
    }

    std::string String::toString() const
    {
        return value_;
    }

    utility::Shared<Value> String::clone() const
    {
        return make(value_);
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
