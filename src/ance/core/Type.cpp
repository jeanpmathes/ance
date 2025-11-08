#include "Type.h"

#include <vector>

namespace
{
    std::vector<ance::core::Type const*> registry;

    uint32_t registerType(ance::core::Type const* type)
    {
        registry.push_back(type);
        return static_cast<uint32_t>(registry.size() - 1);
    }

    ance::core::Type const& getType(uint32_t const index)
    {
        return *registry.at(index);
    }
}

namespace ance::core
{
    Type::Type(Identifier const& identifier)
    : identifier_(identifier), index_(registerType(this))
    {}

    Identifier const& Type::name() const
    {
        return identifier_;
    }

    Type const& Type::Bool()
    {
        static Type const type {Identifier::like("Bool")};
        return type;
    }

    Type const& Type::Unit()
    {
        static Type const type {Identifier::like("Unit")};
        return type;
    }

    Type const& Type::Size()
    {
        static Type const type {Identifier::like("Size")};
        return type;
    }

    Type const& Type::String()
    {
        static Type const type {Identifier::like("String")};
        return type;
    }

    Type const& Type::EntityRef()
    {
        static Type const type {Identifier::like("EntityRef")};
        return type;
    }

    Type const& Type::Ident()
    {
        static Type const type {Identifier::like("Identifier")};
        return type;
    }

    Type const& Type::Function()
    {
        static Type const type {Identifier::like("Function")};
        return type;
    }

    Type const& Type::Self()
    {
        static Type const type {Identifier::like("Type")};
        return type;
    }

    Type const& Type::Scope()
    {
        static Type const type {Identifier::like("Scope")};
        return type;
    }

    Type const& Type::Location()
    {
        static Type const type {Identifier::like("Location")};
        return type;
    }

    Type const& Type::Any()
    {
        static Type const type {Identifier::like("Any")};
        return type;
    }

    Type const& Type::byID(TypeID const& id)
    {
        return getType(id.id);
    }

    TypeID Type::id() const
    {
        return TypeID {.app = 0, .id = index_};
    }

    bool Type::operator==(Type const& other) const
    {
        return &other == this;
    }

    bool Type::operator!=(Type const& other) const
    {
        return !(*this == other);
    }

    bool Type::isAssignableTo(Type const& other) const
    {
        if (other == Any())
            return true;

        return *this == other;
    }
}

std::ostream& operator<<(std::ostream& out, ance::core::Type const& type)
{
    return out << type.name();
}
