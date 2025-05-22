#include "Type.h"

namespace ance::core
{
    Type::Type(Identifier const& identifier) : identifier_(identifier) {}

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

    bool Type::operator==(Type const& other) const
    {
        return &other == this;
    }

    bool Type::operator!=(Type const& other) const
    {
        return !(*this == other);
    }
}

std::ostream& operator<<(std::ostream& out, ance::core::Type const& type)
{
    return out << type.name();
}
