#include "Value.h"

#include "Entity.h"

namespace ance::core
{
    Value::Value(Type const& type, Storage const& value) : type_(type), value_(value) {}

    utility::Shared<Value> Value::makeBool(bool const value)
    {
        return utility::makeShared<Value>(Type::Bool(), value);
    }

    utility::Shared<Value> Value::makeUnit()
    {
        return utility::makeShared<Value>(Type::Unit(), std::monostate{});
    }

    utility::Shared<Value> Value::makeSize(size_t value)
    {
        return utility::makeShared<Value>(Type::Size(), value);
    }

    utility::Shared<Value> Value::makeEntityRef(Entity const& entity)
    {
        return utility::makeShared<Value>(Type::EntityRef(), &entity);
    }

    utility::Shared<Value> Value::makeIdentifier(Identifier const& identifier)
    {
        return utility::makeShared<Value>(Type::Ident(), identifier);
    }

    utility::Shared<Value> Value::makeType(Type const& type)
    {
        return utility::makeShared<Value>(Type::Self(), type.id());
    }

    utility::Shared<Value> Value::makeScope(void* scope)
    {
        return utility::makeShared<Value>(Type::Scope(), scope);
    }

    utility::Shared<Value> Value::makeDefault(Type const& type)
    {
        // Use std::monostate for default
        return utility::makeShared<Value>(type, std::monostate{});
    }

    Type const& Value::type() const
    {
        return type_;
    }

    std::string Value::toString() const
    {
        if (type_ == Type::Bool()) { return std::get<bool>(value_) ? "true" : "false"; }
        if (type_ == Type::Unit()) { return "()"; }
        if (type_ == Type::Size()) { return std::to_string(std::get<size_t>(value_)); }
        if (type_ == Type::EntityRef()) { return "@" + std::string(std::get<Entity const*>(value_)->name().text()); }
        if (type_ == Type::Ident()) { return "#" + std::string(std::get<Identifier>(value_).text()); }
        if (type_ == Type::Self()) { return std::string(Type::byID(std::get<TypeID>(value_)).name().text()); }
        if (type_ == Type::Scope()) { return "<scope>"; }
        return "unknown";
    }

    bool Value::getBool() const
    {
        if (!std::holds_alternative<bool>(value_)) throw std::bad_variant_access();
        return std::get<bool>(value_);
    }

    size_t Value::getSize() const
    {
        if (!std::holds_alternative<size_t>(value_)) throw std::bad_variant_access();
        return std::get<size_t>(value_);
    }

    Entity const& Value::getEntity() const
    {
        if (!std::holds_alternative<Entity const*>(value_)) throw std::bad_variant_access();
        return *std::get<Entity const*>(value_);
    }

    Identifier const& Value::getIdentifier() const
    {
        if (!std::holds_alternative<Identifier>(value_)) throw std::bad_variant_access();
        return std::get<Identifier>(value_);
    }

    Type const& Value::getType() const
    {
        if (!std::holds_alternative<TypeID>(value_)) throw std::bad_variant_access();
        return Type::byID(std::get<TypeID>(value_));
    }

    void* Value::getScope() const
    {
        if (!std::holds_alternative<void*>(value_)) throw std::bad_variant_access();
        return std::get<void*>(value_);
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
