#ifndef ANCE_SRC_LANG_SCOPE_ORDEREDSCOPE_H_
#define ANCE_SRC_LANG_SCOPE_ORDEREDSCOPE_H_

#include "Scope.h"

#include <set>

#include "lang/Assigner.h"
#include "lang/utility/Identifier.h"

namespace lang
{
    /**
     * A scope in which the order of definitions matters.
     * Redefinitions of names are allowed.
     */
    class OrderedScope : public virtual Scope
    {
      public:
        OrderedScope* asOrderedScope() override;

        [[nodiscard]] bool isNameConflicted(lang::Identifier const& name) const override;

        void addDescription(Owned<lang::Description> description) override;
        void addEntity(lang::OwningHandle<lang::Entity> entity) override;

        /**
         * Prepare the definition of a new entity. This will block resolution above this scope.
         * @param name The name of the entity.
         */
        void prepareDefinition(Identifier name);

        /**
         * Erase an entity. An entity must be defined in this scope to be erased.
         * @param entity The entity to erase.
         * @return True if the entity was erased, false otherwise.
         */
        bool erase(lang::ResolvingHandle<lang::Entity> entity);

        /**
         * Check if an entity with the specified name was defined and then erased.
         * @param entity The entity to check.
         * @return True if the entity was erased, false otherwise.
         */
        [[nodiscard]] bool wasEntityErased(lang::Entity const& entity) const;

        void onRegisterUsage(lang::ResolvingHandle<lang::Entity> entity) override;

        Optional<OwningHandle<lang::Entity>> connectWithDefinitionAccordingToOrdering(
            lang::OwningHandle<lang::Entity> variable) override;

        void         resolve() override;
        virtual void resolveFollowingOrder() = 0;
        void         postResolve() override;

        bool resolveDefinition(lang::ResolvingHandle<lang::Entity> entity) override;

        void         buildEntityDeclarations(Execution& exec) const override;
        virtual void buildEntityDeclarationsFollowingOrder(Execution& exec) const = 0;
        void         buildEntityFinalizations(Execution& exec) const override;

      private:
        std::set<lang::Identifier> blockers_ {};

        std::map<lang::Identifier, lang::OwningHandle<lang::Entity>>              undefined_entities_ {};
        std::map<lang::Identifier, lang::OwningHandle<lang::Entity>>              blocked_entities_ {};
        std::map<lang::Identifier, std::vector<lang::OwningHandle<lang::Entity>>> defined_entities_ {};
        std::map<lang::Identifier, lang::ResolvingHandle<lang::Entity>>           active_entities_ {};

        std::map<lang::Identifier, std::vector<Owned<lang::Description>>> descriptions_ {};
    };
}

#endif
