#include "ValueExtensions.h"

#include <utility>

#include "ance/bbt/Type.h"
#include "ance/cet/Scope.h"
#include "ance/cet/Variable.h"

namespace ance::cet
{
    ScopeRef::ScopeRef(Scope& scope, bbt::TypeContext& type_context) : Value(type_context.getScopeRef(), type_context), scope_(scope) {}

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

    VariableRef::VariableRef(Variable& variable, bbt::TypeContext& type_context) : Value(type_context.getVariableRef(), type_context), variable_(variable) {}

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

    LReference::LReference(Address address, utility::Shared<bbt::Type> referenced_type, bbt::TypeContext& type_context)
        : Value(type_context.getLRef(std::move(referenced_type)), type_context)
        , address_(std::move(address))
    {}

    utility::Shared<LReference> LReference::make(Address address, utility::Shared<bbt::Type> referenced_type, bbt::TypeContext& type_context)
    {
        return utility::makeShared<LReference>(std::move(address), referenced_type, type_context);
    }

    std::string LReference::toString() const
    {
        if (!address().isDefined())
            return "<undefined l-ref>";

        return address().read()->toString();
    }

    Address const& LReference::address() const
    {
        return address_;
    }
}
