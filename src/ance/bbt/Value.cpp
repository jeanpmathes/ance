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

    UnitValue::UnitValue() : Value(core::Type::Unit()) {}

    utility::Shared<UnitValue> UnitValue::make()
    {
        return utility::makeShared<UnitValue>();
    }

    std::string UnitValue::toString() const
    {
        return "()";
    }

    utility::Shared<Value> UnitValue::clone() const
    {
        return make();
    }

    BoolValue::BoolValue(bool const value) : Value(core::Type::Bool()), value_(value) {}

    utility::Shared<BoolValue> BoolValue::make(bool const value)
    {
        return utility::makeShared<BoolValue>(value);
    }

    std::string BoolValue::toString() const
    {
        return value_ ? "true" : "false";
    }

    utility::Shared<Value> BoolValue::clone() const
    {
        return make(value_);
    }

    bool BoolValue::value() const
    {
        return value_;
    }

    SizeValue::SizeValue(size_t const value) : Value(core::Type::Size()), value_(value) {}

    utility::Shared<SizeValue> SizeValue::make(size_t value)
    {
        return utility::makeShared<SizeValue>(value);
    }

    std::string SizeValue::toString() const
    {
        return std::to_string(value_);
    }

    utility::Shared<Value> SizeValue::clone() const
    {
        return make(value_);
    }

    size_t SizeValue::value() const
    {
        return value_;
    }

    IdentifierValue::IdentifierValue(core::Identifier const& identifier) : Value(core::Type::Ident()), identifier_(identifier) {}

    utility::Shared<IdentifierValue> IdentifierValue::make(core::Identifier const& identifier)
    {
        return utility::makeShared<IdentifierValue>(identifier);
    }

    std::string IdentifierValue::toString() const
    {
        return "#" + std::string(identifier_.text());
    }

    utility::Shared<Value> IdentifierValue::clone() const
    {
        return make(identifier_);
    }

    core::Identifier const& IdentifierValue::value() const
    {
        return identifier_;
    }

    TypeValue::TypeValue(core::Type const& type) : Value(core::Type::Self()), type_(type) {}

    utility::Shared<TypeValue> TypeValue::make(core::Type const& type)
    {
        return utility::makeShared<TypeValue>(type);
    }

    std::string TypeValue::toString() const
    {
        return std::string(type_.name().text());
    }

    utility::Shared<Value> TypeValue::clone() const
    {
        return make(type_);
    }

    core::Type const& TypeValue::value() const
    {
        return type_;
    }

    LocationValue::LocationValue(core::Location const& location) : Value(core::Type::Location()), location_(location) {}

    utility::Shared<LocationValue> LocationValue::make(core::Location const& location)
    {
        return utility::makeShared<LocationValue>(location);
    }

    std::string LocationValue::toString() const
    {
        std::stringstream ss;
        ss << location_;
        return ss.str();
    }

    utility::Shared<Value> LocationValue::clone() const
    {
        return make(location_);
    }

    core::Location const& LocationValue::value() const
    {
        return location_;
    }

    StringValue::StringValue(std::string value) : Value(core::Type::String()), value_(std::move(value)) {}

    utility::Shared<StringValue> StringValue::make(std::string value)
    {
        return utility::makeShared<StringValue>(std::move(value));
    }

    std::string StringValue::toString() const
    {
        return value_;
    }

    utility::Shared<Value> StringValue::clone() const
    {
        return make(value_);
    }

    std::string const& StringValue::value() const
    {
        return value_;
    }
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Value const& value)
{
    return out << value.toString();
}
