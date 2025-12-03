#ifndef ANCE_CET_SCOPE_H
#define ANCE_CET_SCOPE_H

#include <functional>
#include <map>
#include <set>

#include "ance/utility/Owners.h"

#include "ance/core/Identifier.h"
#include "ance/bbt/Type.h"
#include "ance/core/Location.h"
#include "ance/core/Reporter.h"

#include "ance/bbt/Value.h"
#include "ance/bbt/Node.h"

#include "ance/cet/Variable.h"

namespace ance::cet
{
    class Temporary;
    class Provider;
}

namespace ance::cet
{
    class Scope
    {
      protected:
        explicit Scope(Scope* parent);

      public:
        virtual ~Scope() = default;

        [[nodiscard]] Scope* parent() const;

        [[nodiscard]] utility::Optional<utility::Shared<bbt::Value>> declare(core::Identifier const& identifier,
                                                                              utility::Shared<bbt::Type>       type,
                                                                              bool                    is_final,
                                                                              core::Location const&   location,
                                                                              core::Reporter&         reporter);

        [[nodiscard]] utility::Optional<utility::Shared<bbt::Value>> find(core::Identifier const& identifier);

        Temporary& createTemporary(bbt::Temporary const& bbt_temporary);
        Temporary& getTemporary(bbt::Temporary const& bbt_temporary);

        Scope& addChildScope(utility::Owned<Scope> child_scope);
        void removeChildScope(Scope& scope);

      protected:
        [[nodiscard]] virtual bool                                                         canDeclare(core::Identifier const& identifier) const = 0;
        virtual void                                                                       onDeclare(utility::Owned<Variable> variable)   = 0;
        [[nodiscard]] virtual Variable* onFind(core::Identifier const& identifier)  = 0;

      private:
        Scope* parent_;

        std::map<bbt::Temporary const*, utility::Owned<Temporary>> temporaries_ = {};
        std::list<utility::Owned<Scope>> child_scopes_ = {};
    };

    class GlobalScope final : public Scope
    {
      public:
        explicit GlobalScope(utility::List<utility::Owned<Provider>>& providers);

        ~GlobalScope() override = default;

      protected:
        [[nodiscard]] bool canDeclare(core::Identifier const& identifier) const override;
        void onDeclare(utility::Owned<Variable> variable) override;

        [[nodiscard]] Variable* onFind(core::Identifier const& identifier) override;

      private:
        utility::List<utility::Owned<Provider>>& providers_;

        std::map<core::Identifier, utility::Shared<Variable>> variables_ = {};
    };

    class OrderedScope final : public Scope
    {
      public:
        explicit OrderedScope(Scope& parent);

        ~OrderedScope() override = default;

      protected:
        [[nodiscard]] bool canDeclare(core::Identifier const& identifier) const override;
        void onDeclare(utility::Owned<Variable> variable) override;

        [[nodiscard]] Variable* onFind(core::Identifier const& identifier) override;

      private:
        std::vector<utility::Owned<Variable>> all_variables_ = {};
        std::map<core::Identifier, std::reference_wrapper<Variable>> active_variables_ = {};
        std::set<core::Identifier> outer_identifiers_ = {};
    };

    class UnorderedScope final : public Scope
    {
      public:
        explicit UnorderedScope(Scope& parent);

        ~UnorderedScope() override = default;

      protected:
        [[nodiscard]] bool canDeclare(core::Identifier const& identifier) const override;
        void onDeclare(utility::Owned<Variable> variable) override;

        [[nodiscard]] Variable* onFind(core::Identifier const& identifier) override;

      private:
        std::vector<utility::Owned<Variable>> all_variables_ = {};
        std::map<core::Identifier, std::reference_wrapper<Variable>> variables_ = {};
    };

}

#endif
