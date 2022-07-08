#include "Member.h"

#include "lang/scope/Scope.h"

lang::Member::Member(lang::AccessModifier              access,
                     lang::Identifier                  name,
                     lang::ResolvingHandle<lang::Type> type,
                     lang::Location                    location,
                     lang::Location                    type_location)
    : access_(access)
    , name_(name)
    , type_(type)
    , location_(location)
    , type_location_(type_location)
{}

lang::AccessModifier lang::Member::access() const
{
    return access_;
}

const lang::Identifier& lang::Member::name() const
{
    return name_;
}

lang::ResolvingHandle<lang::Type> lang::Member::type() const
{
    return type_;
}

lang::Location lang::Member::location() const
{
    return location_;
}

lang::Location lang::Member::typeLocation() const
{
    return type_location_;
}

void lang::Member::setScope(lang::Scope* scope)
{
    scope->addType(type());
}