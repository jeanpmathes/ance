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
         * Drop an. An entity must be defined in this scope to be dropped.
         * @param entity The entity to drop.
         * @return True if the entity was dropped, false otherwise.
         */
        bool drop(lang::ResolvingHandle<lang::Entity> entity);

        /**
         * Check if an entity with the specified name was defined and then dropped.
         * @param entity The entity to check.
         * @return True if the entity was dropped, false otherwise.
         */
        [[nodiscard]] bool wasEntityDropped(lang::Entity const& entity) const;

        void onRegisterUsage(lang::ResolvingHandle<lang::Entity> entity) override;

        Optional<OwningHandle<lang::Entity>> connectWithDefinitionAccordingToOrdering(
            lang::OwningHandle<lang::Entity> variable) override;

        void resolve() override;
        void postResolve() override;

        bool resolveDefinition(lang::ResolvingHandle<lang::Entity> entity) override;

        /**
         * Build all variable declarations.
         * @param context The current compile context.
         */
        void buildDeclarations(CompileContext& context);
        void buildFinalization(CompileContext& context) override;

      protected:
        void onSubScope(Scope* sub_scope) override;

      private:
        std::set<lang::Identifier> blockers_ {};

        std::map<lang::Identifier, lang::OwningHandle<lang::Entity>>              undefined_entities_ {};
        std::map<lang::Identifier, lang::OwningHandle<lang::Entity>>              blocked_entities_ {};
        std::map<lang::Identifier, std::vector<lang::OwningHandle<lang::Entity>>> defined_entities_ {};
        std::map<lang::Identifier, lang::ResolvingHandle<lang::Entity>>           active_entities_ {};

        std::map<lang::Identifier, std::vector<Owned<lang::Description>>> descriptions_ {};

        std::vector<lang::Scope*> sub_scopes_;
    };
}

#endif
