#include "Entity.h"

ance::core::Function* ance::core::Entity::asFunction()
{
    return nullptr;
}

ance::core::Function const* ance::core::Entity::asFunction() const
{
    return nullptr;
}

ance::core::Variable* ance::core::Entity::asVariable()
{
    return nullptr;
}

ance::core::Variable const* ance::core::Entity::asVariable() const
{
    return nullptr;
}

std::ostream& operator<<(std::ostream& out, ance::core::Entity const& entity)
{
    out << entity.name();
    return out;
}
