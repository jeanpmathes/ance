#include "Value.h"

#include "Type.h"

namespace ance::core
{
    Value::Value(Type const& type, size_t const value) : type_(type), value_(value) {}

    utility::Shared<Value> Value::makeBool(bool const value)
    {
        return utility::makeShared<Value>(Type::Bool(), value ? 1z : 0z);
    }

    utility::Shared<Value> Value::makeUnit()
    {
        return utility::makeShared<Value>(Type::Unit(), 0z);
    }

    utility::Shared<Value> Value::makeSize(size_t value)
    {
        return utility::makeShared<Value>(Type::Size(), value);
    }

    utility::Shared<Value> Value::makeDefault(Type const& type)
    {
        return utility::makeShared<Value>(type, 0);
    }

    Type const& Value::type() const
    {
        return type_;
    }

    std::string Value::toString() const
    {
        if (type_ == Type::Bool()) { return value_ ? "true" : "false"; }

        if (type_ == Type::Unit()) { return "()"; }

        if (type_ == Type::Size()) { return std::to_string(value_); }

        return "unknown";
    }

    bool Value::getBool() const
    {
        return value_ != 0;
    }

    size_t Value::getSize() const
    {
        return value_;
    }

    utility::Shared<Value> Value::clone() const
    {
        return utility::makeShared<Value>(type_, value_);
    }
}

std::ostream& operator<<(std::ostream& out, ance::core::Value const& value)
{
    return out << value.toString();
}
