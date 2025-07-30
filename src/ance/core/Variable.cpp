#include "Variable.h"

namespace ance::core
{
    Variable::Variable(Identifier const& identifier, Location const& location)
        : identifier_(identifier), location_(location) {}

    Identifier const& Variable::name() const
    {
        return identifier_;
    }

    Location const& Variable::location() const
    {
        return location_;
    }

    Variable* Variable::asVariable()
    {
        return this;
    }
}
