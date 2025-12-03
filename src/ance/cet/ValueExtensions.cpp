#include "ValueExtensions.h"

#include <utility>

#include "ance/cet/Scope.h"
#include "ance/cet/Variable.h"

namespace ance::cet
{
    ScopeRef::ScopeRef(Scope& scope) : Value(bbt::Type::ScopeRef()), scope_(scope) {}

    utility::Shared<ScopeRef> ScopeRef::make(Scope& scope)
    {
        return utility::makeShared<ScopeRef>(scope);
    }

    std::string ScopeRef::toString() const
    {
        return "<scope>";
    }

    Scope& ScopeRef::value() const
    {
        return scope_;
    }

    VariableRef::VariableRef(Variable& variable) : Value(bbt::Type::VariableRef()), variable_(variable) {}

    utility::Shared<VariableRef> VariableRef::make(Variable& variable)
    {
        return utility::makeShared<VariableRef>(variable);
    }

    std::string VariableRef::toString() const
    {
        return "@" + std::string(variable_.name().text());
    }

    Variable& VariableRef::value() const
    {
        return variable_;
    }

    LReference::LReference(Address address) : Value(bbt::Type::LRef()), address_(std::move(address)) {}

    utility::Shared<LReference> LReference::make(Address address)
    {
        return utility::makeShared<LReference>(std::move(address));
    }

    std::string LReference::toString() const
    {
        return address().read()->toString();
    }

    Address const& LReference::address() const
    {
        return address_;
    }
}
