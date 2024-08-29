#ifndef ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_DESCRIPTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_DESCRIPTION_H_

#include "lang/Element.h"

#include "lang/Accessibility.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Scope;
    class Identifier;
    class Context;
}

class ValidationLogger;
class Storage;

namespace lang
{
    /**
     * Base class for all descriptions.
     * Descriptions are parts of the code that describe entities like functions, variables, etc.
     */
    class Description : public virtual Visitable<ANCE_CONSTRUCTS>
    {
      public:
        explicit Description(lang::Accessibility accessibility);
        ~Description() override = default;

      public:
        [[nodiscard]] virtual lang::Identifier const& name() const              = 0;
        [[nodiscard]] virtual bool                    isOverloadAllowed() const = 0;
        [[nodiscard]] lang::Accessibility             access() const;
        [[nodiscard]] virtual bool                    isCMP() const = 0;

        struct Dependency {
            std::reference_wrapper<lang::Entity const> entity;
            bool                                       depends_on_definition = true;

            explicit Dependency(lang::Entity const& dependee, bool depends_on_dependee_definition = true)
                : entity(dependee)
                , depends_on_definition(depends_on_dependee_definition)
            {}
        };

        [[nodiscard]] virtual std::vector<std::reference_wrapper<lang::Entity const>> getProvidedEntities() const = 0;
        [[nodiscard]] virtual std::vector<Dependency> getDeclarationDependencies() const                          = 0;
        [[nodiscard]] virtual std::vector<Dependency> getDefinitionDependencies() const                           = 0;

        /**
         * Initialize the description, which will add the described entity to the passed scope.
         * @param scope The scope.
         */
        void initialize(lang::Scope& scope);

        /**
         * Resolve all entities required for the declaration.
         */
        virtual void resolveDeclaration();

        /**
         * Resolve all entities required for the definition.
         */
        virtual void resolveDefinition();

        /**
         * Called after all entities have been resolved.
         */
        virtual void postResolve();

        /**
         * Validate the description.
         * @param validation_logger The logger to log validation errors to.
         */
        virtual void validate(ValidationLogger& validation_logger) const = 0;

        using Descriptions = std::vector<Owned<Description>>;

        /**
         * Expand the description into one or more descriptions without syntactic sugar.
         * @param new_context The context to use for the expanded descriptions.
         * @return The expanded descriptions.
         */
        [[nodiscard]] virtual Descriptions expand(lang::Context& new_context) const = 0;

        /**
         * Check if the description is imported.
         * @return True if the description is imported.
         */
        [[nodiscard]] bool isImported() const;

        virtual void performInitialization(Execution& exec);
        virtual void performFinalization(Execution& exec);

      protected:
        /**
         * Set the containing scope. Must be called exactly once, before the description is used.
         * @param scope The scope.
         */
        void setScope(Scope& scope);

        virtual void performInitialization() = 0;

        Scope&                     scope();
        [[nodiscard]] Scope const& scope() const;

      public:
        virtual void sync(Storage& storage) = 0;

      private:
        lang::Accessibility accessibility_;
        Scope*              scope_ {nullptr};
    };

    void synchronize(Description** description, Storage& storage);
}

#endif
