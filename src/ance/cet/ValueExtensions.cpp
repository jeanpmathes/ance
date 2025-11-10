#include "ValueExtensions.h"

#include "ance/cet/Scope.h"
#include "ance/cet/Variable.h"

namespace ance::cet
{
    ScopeValue::ScopeValue(Scope& scope) : Value(core::Type::Scope()), scope_(scope) {}

    utility::Shared<ScopeValue> ScopeValue::make(Scope& scope)
    {
        return utility::makeShared<ScopeValue>(scope);
    }

    std::string ScopeValue::toString() const
    {
        return "<scope>";
    }

    utility::Shared<bbt::Value> ScopeValue::clone() const
    {
        return make(scope_);
    }

    Scope& ScopeValue::value() const
    {
        return scope_;
    }

    VariableRefValue::VariableRefValue(Variable const& variable) : Value(core::Type::VariableRef()), variable_(variable) {}

    utility::Shared<VariableRefValue> VariableRefValue::make(Variable const& variable)
    {
        return utility::makeShared<VariableRefValue>(variable);
    }

    std::string VariableRefValue::toString() const
    {
        return "@" + std::string(variable_.name().text());
    }

    utility::Shared<bbt::Value> VariableRefValue::clone() const
    {
        return make(variable_);
    }

    Variable const& VariableRefValue::value() const
    {
        return variable_;
    }
}
