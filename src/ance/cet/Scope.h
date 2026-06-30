#ifndef ANCE_CET_SCOPE_H
#define ANCE_CET_SCOPE_H

#include <functional>
#include <map>
#include <set>
#include <variant>

#include "ance/utility/Owners.h"

#include "ance/bbt/Type.h"
#include "ance/core/Identifier.h"
#include "ance/core/Location.h"
#include "ance/core/Reporter.h"

#include "ance/bbt/Node.h"
#include "ance/bbt/Value.h"

#include "ance/cet/Variable.h"

namespace ance::cet
{
    class Temporary;
}

namespace ance::cet
{
    enum class DeclarationCheckResult
    {
        OK,
        BLOCKS_OUTER,
        ALREADY_DEFINED,
    };

    enum class EraseResult
    {
        OK,
        NOT_FOUND,
        IS_OUTER,
        IS_NOT_ORDERED,
    };

    struct FindResult
    {
        enum class Status
        {
            FOUND,
            NOT_FOUND,
            ERASED,
        };

        struct NotFound
        {
        };
        struct Erased
        {
            core::Location erase_location;
        };

        utility::Optional<utility::Shared<bbt::Value const>> value;
        Status                                         status;
        std::variant<NotFound, Erased>                 reason;

        static FindResult found(utility::Shared<bbt::Value const> value);
        static FindResult notFound();
        static FindResult erased(core::Location const& location);
    };

    class Scope
    {
      protected:
        explicit Scope(Scope* parent, bbt::TypeContext& type_context);

      public:
        virtual ~Scope() = default;

        [[nodiscard]] Scope* parent() const;

        [[nodiscard]] utility::Optional<utility::Shared<bbt::Value const>> declare(core::Identifier const&          identifier,
                                                                                   utility::Shared<bbt::Type const> type,
                                                                                   bool                       is_variable,
                                                                             core::Location const&      location,
                                                                             core::Reporter&            reporter);

        [[nodiscard]] FindResult  find(core::Identifier const& identifier);
        [[nodiscard]] EraseResult erase(core::Identifier const& identifier);

        Temporary& createTemporary(bbt::Temporary const& bbt_temporary);
        Temporary& getTemporary(bbt::Temporary const& bbt_temporary);

        Scope& addChildScope(utility::Owned<Scope> child_scope);
        void   removeChildScope(Scope& scope);

      protected:
        [[nodiscard]] virtual DeclarationCheckResult canDeclare(core::Identifier const& identifier) const = 0;
        virtual void                                 onDeclare(utility::Owned<Variable> variable)         = 0;
        [[nodiscard]] virtual FindResult             onFind(core::Identifier const& identifier)           = 0;
        [[nodiscard]] virtual bool                   onContains(core::Identifier const& identifier) const = 0;
        [[nodiscard]] virtual bool                   onErase(core::Identifier const& identifier);

        [[nodiscard]] virtual bool isOrdered() const;

        bbt::TypeContext& types();

      private:
        Scope*            parent_;
        bbt::TypeContext& type_context_;

        std::map<bbt::Temporary const*, utility::Owned<Temporary>> temporaries_  = {};
        std::list<utility::Owned<Scope>>                           child_scopes_ = {};
    };

    /// The core scope, which is the root of all scopes.
    /// Note that it is even higher than the scope of the compiled unit, as it contains core language features and dependencies as well.
    class CoreScope final : public Scope
    {
      public:
        explicit CoreScope(bbt::TypeContext& type_context);

        ~CoreScope() override = default;

      protected:
        [[nodiscard]] DeclarationCheckResult canDeclare(core::Identifier const& identifier) const override;
        void                                 onDeclare(utility::Owned<Variable> variable) override;

        [[nodiscard]] FindResult onFind(core::Identifier const& identifier) override;
        [[nodiscard]] bool       onContains(core::Identifier const& identifier) const override;

      private:
        std::map<core::Identifier, utility::Owned<Variable>> variables_ = {};
    };

    /// An ordered scope defines an order of evalution for the flow contained within.
    /// It is valid to define a name multiple times within an ordered scope, the most recent definition is used.
    class OrderedScope final : public Scope
    {
      public:
        explicit OrderedScope(Scope& parent, bbt::TypeContext& type_context);

        ~OrderedScope() override = default;

      protected:
        [[nodiscard]] DeclarationCheckResult canDeclare(core::Identifier const& identifier) const override;
        void                                 onDeclare(utility::Owned<Variable> variable) override;

        [[nodiscard]] FindResult onFind(core::Identifier const& identifier) override;
        [[nodiscard]] bool       onContains(core::Identifier const& identifier) const override;
        [[nodiscard]] bool       onErase(core::Identifier const& identifier) override;

        [[nodiscard]] bool isOrdered() const override;

      private:
        std::vector<utility::Owned<Variable>>                        all_variables_     = {};
        std::map<core::Identifier, std::reference_wrapper<Variable>> active_variables_  = {};
        std::set<core::Identifier>                                   outer_identifiers_ = {};
        std::map<core::Identifier, core::Location>                   erased_variables_  = {};
    };

    /// An unordered scope contains flows with no required order of evaluation.
    /// This allows evaluation to be suspended and resumed to ensure definitions occur before usage.
    class UnorderedScope final : public Scope
    {
      public:
        explicit UnorderedScope(Scope& parent, bbt::TypeContext& type_context);

        ~UnorderedScope() override = default;

      protected:
        [[nodiscard]] DeclarationCheckResult canDeclare(core::Identifier const& identifier) const override;
        void                                 onDeclare(utility::Owned<Variable> variable) override;

        [[nodiscard]] FindResult onFind(core::Identifier const& identifier) override;
        [[nodiscard]] bool       onContains(core::Identifier const& identifier) const override;

      private:
        std::vector<utility::Owned<Variable>>                        all_variables_ = {};
        std::map<core::Identifier, std::reference_wrapper<Variable>> variables_     = {};
    };

}

#endif
