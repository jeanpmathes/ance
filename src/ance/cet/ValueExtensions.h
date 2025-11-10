#ifndef ANCE_CET_VALUEEXTENSIONS_H
#define ANCE_CET_VALUEEXTENSIONS_H

#include "ance/bbt/Value.h"

namespace ance::cet
{
    class Variable;
    class Scope;

    class ScopeValue final : public bbt::Value
    {
    public:
        explicit ScopeValue(Scope& scope);

        static utility::Shared<ScopeValue> make(Scope& scope);

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] Scope& value() const;

    private:
        Scope& scope_;
    };

    class VariableRefValue final : public bbt::Value
    {
    public:
        explicit VariableRefValue(Variable const& variable);

        static utility::Shared<VariableRefValue> make(Variable const& variable);

        ~VariableRefValue() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] Variable const& value() const;

    private:
        Variable const& variable_;
    };
}

#endif
