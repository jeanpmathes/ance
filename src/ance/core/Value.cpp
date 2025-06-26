#include "Value.h"

namespace ance::core
{
    Value::Value(Type const& type, Storage const storage) : type_(type), storage_(storage) {}

    utility::Shared<Value> Value::makeBool(bool const value)
    {
        Storage storage;
        storage.boolean = value;

        return utility::makeShared<Value>(Type::Bool(), storage);
    }

    utility::Shared<Value> Value::makeUnit()
    {
        Storage storage;
        storage.size = 0; // Just to initialize the union, as it will not be used.

        return utility::makeShared<Value>(Type::Unit(), storage);
    }

    utility::Shared<Value> Value::makeSize(size_t value)
    {
        Storage storage;
        storage.size = value;

        return utility::makeShared<Value>(Type::Size(), storage);
    }

    utility::Shared<Value> Value::makeType(Type const& type)
    {
        Storage storage;
        storage.type_id = type.id();

        return utility::makeShared<Value>(Type::Self(), storage);
    }

    utility::Shared<Value> Value::makeDefault(Type const& type)
    {
        return utility::makeShared<Value>(type, Storage {});
    }

    Type const& Value::type() const
    {
        return type_;
    }

    std::string Value::toString() const
    {
        if (type_ == Type::Bool()) { return storage_.boolean ? "true" : "false"; }

        if (type_ == Type::Unit()) { return "()"; }

        if (type_ == Type::Size()) { return std::to_string(storage_.size); }

        if (type_ == Type::Self())
        {
            return std::string(Type::byID(storage_.type_id).name().text());
        }

        return "unknown";
    }

    bool Value::getBool() const
    {
        return storage_.boolean;
    }

    size_t Value::getSize() const
    {
        return storage_.size;
    }

    Type const& Value::getType() const
    {
        return Type::byID(storage_.type_id);
    }

    utility::Shared<Value> Value::clone() const
    {
        return utility::makeShared<Value>(type_, storage_);
    }
}

std::ostream& operator<<(std::ostream& out, ance::core::Value const& value)
{
    return out << value.toString();
}
