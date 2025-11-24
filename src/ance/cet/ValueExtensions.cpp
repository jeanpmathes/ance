#include "ValueExtensions.h"

#include <utility>

#include "ance/cet/Scope.h"
#include "ance/cet/Variable.h"

namespace ance::cet
{
    ScopeRef::ScopeRef(Scope& scope) : Value(core::Type::Scope()), scope_(scope) {}

    utility::Shared<ScopeRef> ScopeRef::make(Scope& scope)
    {
        return utility::makeShared<ScopeRef>(scope);
    }

    std::string ScopeRef::toString() const
    {
        return "<scope>";
    }

    utility::Shared<bbt::Value> ScopeRef::clone() const
    {
        return make(scope_);
    }

    Scope& ScopeRef::value() const
    {
        return scope_;
    }

    VariableRef::VariableRef(Variable& variable) : Value(core::Type::VariableRef()), variable_(variable) {}

    utility::Shared<VariableRef> VariableRef::make(Variable& variable)
    {
        return utility::makeShared<VariableRef>(variable);
    }

    std::string VariableRef::toString() const
    {
        return "@" + std::string(variable_.name().text());
    }

    utility::Shared<bbt::Value> VariableRef::clone() const
    {
        return make(variable_);
    }

    Variable& VariableRef::value() const
    {
        return variable_;
    }

    LReference::LReference(Address address) : Value(core::Type::LRef()), address_(std::move(address)) {}

    utility::Shared<LReference> LReference::make(Address address)
    {
        return utility::makeShared<LReference>(std::move(address));
    }

    std::string LReference::toString() const
    {
        return address().read()->toString();
    }

    utility::Shared<bbt::Value> LReference::clone() const
    {
        return make(address_);
    }

    Address const& LReference::address() const
    {
        return address_;
    }
}
