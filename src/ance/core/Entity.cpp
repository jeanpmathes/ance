#include "Entity.h"

ance::core::Function* ance::core::Entity::asFunction()
{
    return nullptr;
}

ance::core::Variable* ance::core::Entity::asVariable()
{
    return nullptr;
}

std::ostream& operator<<(std::ostream& out, ance::core::Entity const& entity)
{
    out << entity.name();
    return out;
}
