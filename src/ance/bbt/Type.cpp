#include "Type.h"

namespace ance::bbt
{
    Type::Type(core::Identifier const& identifier, TypeContext& type_context) : Value(std::nullopt, type_context), identifier_(identifier) {}

    core::Identifier const& Type::name() const
    { return identifier_; }

    bool Type::operator==(Type const& other) const
    { return &other == this; }

    bool Type::operator!=(Type const& other) const
    { return !(*this == other); }

    bool Type::isAssignableTo(Type const& other) const
    { return *this == other; }

    std::string Type::toString() const
    { return std::string(identifier_.text()); }

    utility::Shared<Type> TypeContext::getBool()
    {
        utility::Shared<Type> static type = utility::makeShared<Type>(core::Identifier::like("Bool"), *this);
        return type;
    }

    utility::Shared<Type> TypeContext::getUnit()
    {
        utility::Shared<Type> static type = utility::makeShared<Type>(core::Identifier::like("Unit"), *this);
        return type;
    }

    utility::Shared<Type> TypeContext::getSize()
    {
        utility::Shared<Type> static type = utility::makeShared<Type>(core::Identifier::like("Size"), *this);
        return type;
    }

    utility::Shared<Type> TypeContext::getString()
    {
        utility::Shared<Type> static type = utility::makeShared<Type>(core::Identifier::like("String"), *this);
        return type;
    }

    utility::Shared<Type> TypeContext::getVariableRef()
    {
        utility::Shared<Type> static type = utility::makeShared<Type>(core::Identifier::like(".Variable"), *this);
        return type;
    }

    utility::Shared<Type> TypeContext::getLRef()
    {
        utility::Shared<Type> static type = utility::makeShared<Type>(core::Identifier::like("&T"), *this);
        return type;
    }

    utility::Shared<Type> TypeContext::getIdentifier()
    {
        utility::Shared<Type> static type = utility::makeShared<Type>(core::Identifier::like("Identifier"), *this);
        return type;
    }

    utility::Shared<Type> TypeContext::getFunction()
    {
        utility::Shared<Type> static type = utility::makeShared<Type>(core::Identifier::like("Function"), *this);
        return type;
    }

    utility::Shared<Type> TypeContext::getType()
    {
        utility::Shared<Type> static type = utility::makeShared<Type>(core::Identifier::like("Type"), *this);
        return type;
    }

    utility::Shared<Type> TypeContext::getScopeRef()
    {
        utility::Shared<Type> static type = utility::makeShared<Type>(core::Identifier::like(".Scope"), *this);
        return type;
    }

    utility::Shared<Type> TypeContext::getLocation()
    {
        utility::Shared<Type> static type = utility::makeShared<Type>(core::Identifier::like("Location"), *this);
        return type;
    }
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Type const& type)
{ return out << type.name(); }
