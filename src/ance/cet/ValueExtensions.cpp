#include "ValueExtensions.h"

#include <utility>

#include "ance/bbt/Type.h"
#include "ance/cet/Scope.h"
#include "ance/cet/Variable.h"

namespace ance::cet
{
    ScopeRef::ScopeRef(Scope& scope, bbt::TypeContext& type_context) : Value(type_context.getScopeRef(), type_context), ValueBase(), scope_(scope) {}

    utility::Shared<ScopeRef> ScopeRef::make(Scope& scope, bbt::TypeContext& type_context)
    {
        return utility::makeShared<ScopeRef>(scope, type_context);
    }

    std::string ScopeRef::toString() const
    {
        return "<scope>";
    }

    Scope& ScopeRef::value() const
    {
        return scope_;
    }

    bool ScopeRef::equals(ScopeRef const& other) const
    {
        return &scope_ == &other.scope_;
    }

    VariableRef::VariableRef(Variable& variable, bbt::TypeContext& type_context)
        : Value(type_context.getVariableRef(), type_context)
        , ValueBase()
        , variable_(variable)
    {}

    utility::Shared<VariableRef> VariableRef::make(Variable& variable, bbt::TypeContext& type_context)
    {
        return utility::makeShared<VariableRef>(variable, type_context);
    }

    std::string VariableRef::toString() const
    {
        return "@" + std::string(variable_.name().text());
    }

    Variable& VariableRef::value() const
    {
        return variable_;
    }

    bool VariableRef::equals(VariableRef const& other) const
    {
        return &variable_ == &other.variable_;
    }

    Reference::Reference(Address                         address,
                         utility::Shared<bbt::Type const> referenced_type,
                         core::VariabilityModifier const variability,
                         bbt::TypeContext&               type_context)
        : Value(type_context.getReference(std::move(referenced_type), variability), type_context), ValueBase()
        , address_(std::move(address))
    {}

    utility::Shared<Reference> Reference::make(Address                    address,
                                               utility::Shared<bbt::Type const> referenced_type,
                                               core::VariabilityModifier  variability,
                                               bbt::TypeContext&          type_context)
    {
        return utility::makeShared<Reference>(std::move(address), referenced_type, variability, type_context);
    }

    std::string Reference::toString() const
    {
        if (!address().isDefined()) return "<undefined reference>";

        return address().read()->toString();
    }

    Address const& Reference::address() const
    {
        return address_;
    }

    bool Reference::equals(Reference const& other) const
    {
        return address_.read()->equals(*other.address_.read());
    }
}
