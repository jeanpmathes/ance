#include "Value.h"

#include <sstream>
#include <utility>

#include "ance/bbt/Type.h"

namespace ance::bbt
{
    Value::Value(utility::Optional<utility::Shared<Type>> type, TypeContext& type_context) : type_(std::move(type)), type_context_(type_context) {}

    utility::Shared<Type> Value::type()
    { return type_.valueOr(type_context_.getType()); }

    Type const& Value::type() const
    { return type_.hasValue() ? *type_.value() : *type_context_.getType(); }

    Unit::Unit(TypeContext& type_context) : Value(type_context.getUnit(), type_context) {}

    utility::Shared<Unit> Unit::make(TypeContext& type_context)
    { return utility::makeShared<Unit>(type_context); }

    std::string Unit::toString() const
    { return "()"; }

    Bool::Bool(bool const value, TypeContext& type_context) : Value(type_context.getBool(), type_context), value_(value) {}

    utility::Shared<Bool> Bool::make(bool const value, TypeContext& type_context)
    { return utility::makeShared<Bool>(value, type_context); }

    std::string Bool::toString() const
    { return value_ ? "true" : "false"; }

    bool Bool::value() const
    { return value_; }

    Size::Size(size_t const value, TypeContext& type_context) : Value(type_context.getSize(), type_context), value_(value) {}

    utility::Shared<Size> Size::make(size_t value, TypeContext& type_context)
    { return utility::makeShared<Size>(value, type_context); }

    std::string Size::toString() const
    { return std::to_string(value_); }

    size_t Size::value() const
    { return value_; }

    Identifier::Identifier(core::Identifier const& identifier, TypeContext& type_context)
        : Value(type_context.getIdentifier(), type_context)
        , identifier_(identifier)
    {}

    utility::Shared<Identifier> Identifier::make(core::Identifier const& identifier, TypeContext& type_context)
    { return utility::makeShared<Identifier>(identifier, type_context); }

    std::string Identifier::toString() const
    { return "#" + std::string(identifier_.text()); }

    core::Identifier const& Identifier::value() const
    { return identifier_; }

    Location::Location(core::Location const& location, TypeContext& type_context) : Value(type_context.getLocation(), type_context), location_(location) {}

    utility::Shared<Location> Location::make(core::Location const& location, TypeContext& type_context)
    { return utility::makeShared<Location>(location, type_context); }

    std::string Location::toString() const
    {
        std::stringstream ss;
        ss << location_;
        return ss.str();
    }

    core::Location const& Location::value() const
    { return location_; }

    String::String(std::string value, TypeContext& type_context) : Value(type_context.getString(), type_context), value_(std::move(value)) {}

    utility::Shared<String> String::make(std::string value, TypeContext& type_context)
    { return utility::makeShared<String>(std::move(value), type_context); }

    std::string String::toString() const
    { return value_; }

    std::string const& String::value() const
    { return value_; }
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Value const& value)
{ return out << value.toString(); }
