#include "Type.h"

namespace ance::bbt
{
    Type::Type(core::Identifier const& identifier) : Value(std::nullopt), identifier_(identifier)
    {}

    core::Identifier const& Type::name() const
    {
        return identifier_;
    }

    utility::Shared<Type> Type::Bool()
    {
        static utility::Shared<Type> type = utility::makeShared<Type>(core::Identifier::like("Bool"));
        return type;
    }

    utility::Shared<Type> Type::Unit()
    {
        static utility::Shared<Type> type = utility::makeShared<Type>(core::Identifier::like("Unit"));
        return type;
    }

    utility::Shared<Type> Type::Size()
    {
        static utility::Shared<Type> type = utility::makeShared<Type>(core::Identifier::like("Size"));
        return type;
    }

    utility::Shared<Type> Type::String()
    {
        static utility::Shared<Type> type = utility::makeShared<Type>(core::Identifier::like("String"));
        return type;
    }

    utility::Shared<Type> Type::VariableRef()
    {
        static utility::Shared<Type> type = utility::makeShared<Type>(core::Identifier::like(".Variable"));
        return type;
    }

    utility::Shared<Type> Type::LRef()
    {
        static utility::Shared<Type> type = utility::makeShared<Type>(core::Identifier::like("&T"));
        return type;
    }

    utility::Shared<Type> Type::Ident()
    {
        static utility::Shared<Type> type = utility::makeShared<Type>(core::Identifier::like("Identifier"));
        return type;
    }

    utility::Shared<Type> Type::Function()
    {
        static utility::Shared<Type> type = utility::makeShared<Type>(core::Identifier::like("Function"));
        return type;
    }

    utility::Shared<Type> Type::Self()
    {
        static utility::Shared<Type> type = utility::makeShared<Type>(core::Identifier::like("Type")); // todo: maybe most places that take Type should actually take .Type (reference)
        return type;
    }

    utility::Shared<Type> Type::ScopeRef()
    {
        static utility::Shared<Type> type = utility::makeShared<Type>(core::Identifier::like(".Scope"));
        return type;
    }

    utility::Shared<Type> Type::Location()
    {
        static utility::Shared<Type> type = utility::makeShared<Type>(core::Identifier::like("Location"));
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

    bool Type::isAssignableTo(Type const& other) const
    {
        return *this == other;
    }

    std::string Type::toString() const
    {
        return std::string(identifier_.text());
    }
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Type const& type)
{
    return out << type.name();
}
