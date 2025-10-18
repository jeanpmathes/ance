#include "Variable.h"

namespace ance::core
{
    Variable::Variable(Identifier const& identifier, Type const& type, bool const is_final, Location const& location)
        : identifier_(identifier), type_(type), is_final_(is_final), location_(location) {}

    Identifier const& Variable::name() const
    {
        return identifier_;
    }

    Type const& Variable::type() const
    {
        return type_;
    }

    bool Variable::isFinal() const
    {
        return is_final_;
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
