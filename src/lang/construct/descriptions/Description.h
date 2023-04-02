#ifndef ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_DESCRIPTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_DESCRIPTION_H_

#include "lang/Element.h"

#include "lang/AccessModifier.h"

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
        ~Description() override = default;

      public:
        [[nodiscard]] virtual lang::Identifier const& name() const              = 0;
        [[nodiscard]] virtual bool                    isOverloadAllowed() const = 0;
        [[nodiscard]] virtual lang::AccessModifier    access() const            = 0;

        /**
         * Initialize the description, which will add the described entity to the passed scope.
         * @param scope The scope.
         */
        void initialize(lang::Scope& scope);

        /**
         * Call resolve on owned entities.
         */
        virtual void resolve();

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
        [[nodiscard]] virtual bool isImported() const = 0;

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
        Scope* scope_ {nullptr};
    };

    void synchronize(Description** description, Storage& storage);
}

#endif
