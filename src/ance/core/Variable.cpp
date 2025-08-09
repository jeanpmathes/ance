#include "Variable.h"

namespace ance::core
{
    Variable::Variable(Identifier const& identifier, Type const& type, Location const& location)
        : identifier_(identifier), type_(type), location_(location) {}

    Identifier const& Variable::name() const
    {
        return identifier_;
    }

    Type const& Variable::type() const
    {
        return type_;
    }

    Location const& Variable::location() const
    {
        return location_;
    }

    Variable* Variable::asVariable()
    {
        return this;
    }

    Variable const* Variable::asVariable() const
    {
        return this;
    }
}
