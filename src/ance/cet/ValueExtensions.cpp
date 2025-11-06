#include "ValueExtensions.h"

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
}
