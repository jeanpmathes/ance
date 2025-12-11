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
        ScopeRef(Scope& scope, bbt::TypeContext& type_context);

        static utility::Shared<ScopeRef> make(Scope& scope, bbt::TypeContext& type_context);

        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] Scope& value() const;

      private:
        Scope& scope_;
    };

    class VariableRef final : public bbt::Value
    {
      public:
        VariableRef(Variable& variable, bbt::TypeContext& type_context);

        static utility::Shared<VariableRef> make(Variable& variable, bbt::TypeContext& type_context);

        ~VariableRef() override = default;

        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] Variable& value() const;

      private:
        Variable& variable_;
    };

    class LReference final : public bbt::Value
    {
      public:
        explicit LReference(Address address, bbt::TypeContext& type_context);

        static utility::Shared<LReference> make(Address address, bbt::TypeContext& type_context);

        ~LReference() override = default;

        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] Address const& address() const;

      private:
        Address address_;
    };
}

#endif
