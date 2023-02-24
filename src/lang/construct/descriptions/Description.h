#ifndef ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_DESCRIPTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_DESCRIPTIONS_DESCRIPTION_H_

#include "lang/Element.h"

namespace lang
{
    class Scope;
    class Identifier;
}

class ValidationLogger;

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
         * @return The expanded descriptions.
         */
        [[nodiscard]] virtual Descriptions expand() const = 0;

      protected:
        /**
         * Set the containing scope. Must be called exactly once, before the description is used.
         * @param scope The scope.
         */
        void setScope(Scope& scope);

        virtual void performInitialization() = 0;

        Scope&                     scope();
        [[nodiscard]] Scope const& scope() const;

      private:
        Scope* scope_ {nullptr};
    };
}

#endif
