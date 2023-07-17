#include "Entity.h"

std::string lang::Entity::getAnnotatedName() const
{
    return "'" + std::string(name().text()) + "'";
}

void lang::Entity::setContainingScope(lang::Scope* scope)
{
    assert(scope == this->scope());
}
