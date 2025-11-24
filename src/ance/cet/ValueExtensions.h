#ifndef ANCE_CET_VALUEEXTENSIONS_H
#define ANCE_CET_VALUEEXTENSIONS_H

#include "ance/bbt/Value.h"

#include "ance/cet/Address.h"

namespace ance::cet
{
    class Variable;
    class Scope;

    class ScopeRef final : public bbt::Value
    {
    public:
        explicit ScopeRef(Scope& scope);

        static utility::Shared<ScopeRef> make(Scope& scope);

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] Scope& value() const;

    private:
        Scope& scope_;
    };

    class VariableRef final : public bbt::Value
    {
    public:
        explicit VariableRef(Variable& variable);

        static utility::Shared<VariableRef> make(Variable& variable);

        ~VariableRef() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] Variable& value() const;

    private:
        Variable& variable_;
    };

    class LReference final : public bbt::Value
    {
    public:
        explicit LReference(Address address);

        static utility::Shared<LReference> make(Address address);

        ~LReference() override = default;

        [[nodiscard]] std::string            toString() const override;
        [[nodiscard]] utility::Shared<Value> clone() const override;

        [[nodiscard]] Address const& address() const;

    private:
        Address address_;
    };
}

#endif
