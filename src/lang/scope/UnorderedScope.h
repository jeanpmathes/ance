#ifndef ANCE_SRC_LANG_SCOPE_UNORDEREDSCOPE_H_
#define ANCE_SRC_LANG_SCOPE_UNORDEREDSCOPE_H_

#include "Scope.h"

#include <experimental/vector>
#include <map>
#include <optional>
#include <ranges>
#include <vector>

#include "lang/construct/Function.h"
#include "lang/construct/FunctionGroup.h"
#include "lang/construct/Variable.h"
#include "lang/type/Type.h"
#include "lang/utility/Identifier.h"

class LiteralExpression;
class Storage;

namespace lang
{
    class Description;
}

namespace lang
{
    /**
     * A scope in which the order of definitions does not matter.
     * Redefinitions of names are not allowed.
     */
    class UnorderedScope : public virtual Scope
    {
      public:
        [[nodiscard]] bool isNameConflicted(lang::Identifier const& name) const override;

        void addDescription(Owned<lang::Description> description) override;
        void addEntity(lang::OwningHandle<lang::Entity> entity) override;

        /**
         * Get an entity defined in this scope by it's name.
         * @param string The name of the entity.
         * @return The entity, or nothing if no such entity is defined.
         */
        Optional<lang::ResolvingHandle<lang::Entity>> getEntity(Identifier string);

        /**
         * Validate the descriptions in this scope. In contrast to an ordered scope, the unordered scope owns the contained descriptions, which is why it validates them.
         * @param validation_logger The logger to log errors to.
         * @return True if all descriptions are valid, false otherwise.
         */
        bool validate(ValidationLogger& validation_logger) const;

        void onRegisterUsage(lang::ResolvingHandle<lang::Entity> entity) override;

        void resolve() override;
        void postResolve() override;

        bool resolveDefinition(lang::ResolvingHandle<lang::Entity> entity) override;

        [[nodiscard]] std::vector<std::reference_wrapper<lang::Type const>>        getUsedBuiltInTypes() const;
        [[nodiscard]] std::vector<std::reference_wrapper<lang::Description const>> getDescriptionsInDeclarationOrder()
            const;
        [[nodiscard]] std::vector<std::reference_wrapper<lang::Description const>> getDescriptionsInDefinitionOrder()
            const;

        /**
         * Build all initialization required by global entities.
         * @param exec The current execution context.
         */
        void performEntityInitializations(Execution& exec) const;

        void performEntityFinalizations(Execution& exec) const override;

      protected:
        virtual void onResolve() {}
        virtual void onPostResolve() {}

        struct AssociatedDescription {
            Optional<std::string>    source;
            Owned<lang::Description> description;

            AssociatedDescription(Optional<std::string> new_source, Owned<lang::Description> new_description)
                : source(std::move(new_source))
                , description(std::move(new_description))
            {}
        };

        [[nodiscard]] std::map<lang::Identifier, std::vector<AssociatedDescription>>&       getCompatibleDescriptions();
        [[nodiscard]] std::map<lang::Identifier, std::vector<AssociatedDescription>> const& getCompatibleDescriptions()
            const;

      public:
        [[nodiscard]] std::vector<lang::ResolvingHandle<lang::FunctionGroup>>        getFunctionGroups();
        [[nodiscard]] std::vector<std::reference_wrapper<lang::FunctionGroup const>> getFunctionGroups() const;

      private:
        lang::ResolvingHandle<lang::FunctionGroup> prepareDefinedFunctionGroup(Identifier name);

      private:
        std::map<lang::Identifier, std::vector<AssociatedDescription>> compatible_descriptions_;
        std::map<lang::Identifier, std::vector<AssociatedDescription>> incompatible_descriptions_;

        std::set<lang::Identifier> defined_names_;

        std::map<lang::Identifier, lang::OwningHandle<lang::Entity>> undefined_entities_;
        std::map<lang::Identifier, lang::OwningHandle<lang::Entity>> defined_entities_;

        std::vector<lang::Identifier> missing_declarations_;
        std::vector<lang::Identifier> missing_definitions_;
        std::vector<lang::Identifier> cyclic_definitions_;

        enum ResolvableKind
        {
            DECLARATION,
            DEFINITION
        };

        struct ResolvableGroup {
            std::vector<std::reference_wrapper<lang::Description>> descriptions;
            ResolvableKind                                         kind;
        };

        Optional<std::vector<ResolvableGroup>> description_order_;
    };
}

#endif
