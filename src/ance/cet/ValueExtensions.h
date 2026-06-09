#ifndef ANCE_CET_VALUEEXTENSIONS_H
#define ANCE_CET_VALUEEXTENSIONS_H

#include "ance/core/VariabilityModifier.h"

#include "ance/bbt/Value.h"

#include "ance/cet/Address.h"

namespace ance::cet
{
    class Variable;
    class Scope;

    class ScopeRef final : public bbt::ValueBase<ScopeRef>
    {
      public:
        ScopeRef(Scope& scope, bbt::TypeContext& type_context);

        static utility::Shared<ScopeRef> make(Scope& scope, bbt::TypeContext& type_context);

        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] Scope&      value() const;
        [[nodiscard]] bool        equals(ScopeRef const& other) const override;

      private:
        Scope& scope_;
    };

    class VariableRef final : public bbt::ValueBase<VariableRef>
    {
      public:
        VariableRef(Variable& variable, bbt::TypeContext& type_context);

        static utility::Shared<VariableRef> make(Variable& variable, bbt::TypeContext& type_context);

        ~VariableRef() override = default;

        [[nodiscard]] std::string toString() const override;
        [[nodiscard]] Variable&   value() const;
        [[nodiscard]] bool        equals(VariableRef const& other) const override;

      private:
        Variable& variable_;
    };

    class Reference final : public bbt::ValueBase<Reference>
    {
      public:
        Reference(Address address, utility::Shared<bbt::Type> referenced_type, core::VariabilityModifier variability, bbt::TypeContext& type_context);

        static utility::Shared<Reference> make(Address                    address,
                                               utility::Shared<bbt::Type> referenced_type,
                                               core::VariabilityModifier  variability,
                                               bbt::TypeContext&          type_context);

        ~Reference() override = default;

        [[nodiscard]] std::string    toString() const override;
        [[nodiscard]] Address const& address() const;
        [[nodiscard]] bool           equals(Reference const& other) const override;

      private:
        Address address_;
    };
}

#endif
