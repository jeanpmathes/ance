#ifndef ANCE_SRC_LANG_CONSTRUCT_VARIABLEDEFINITION_H_
#define ANCE_SRC_LANG_CONSTRUCT_VARIABLEDEFINITION_H_

#include "lang/Element.h"
#include "lang/construct/value/Value.h"
#include "lang/utility/Location.h"

namespace lang
{
    class Scope;
    class Type;
}

class ValidationLogger;
class CompileContext;

namespace lang
{
    /**
     * Defines the behaviour of a variable.
     */
    class VariableDefinition : public virtual lang::Visitable<ANCE_CONSTRUCTS>
    {
      public:
        VariableDefinition(lang::ResolvingHandle<lang::Variable> self,
                           lang::ResolvingHandle<lang::Type>     type,
                           lang::Location                        type_location,
                           Scope&                                containing_scope,
                           bool                                  is_final,
                           lang::Location                        location);

        [[nodiscard]] Identifier const& name() const;

        /**
         * Get the scope in which this variable is defined.
         */
        [[nodiscard]] lang::Scope* scope() const;

        /**
         * Get the type of this variable.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Type> type();
        /**
         * Get the type of this variable.
         */
        [[nodiscard]] lang::Type const& type() const;

        /**
         * Get the source location of the variable definition.
         */
        [[nodiscard]] lang::Location location() const;

        /**
         * Get the source location of the type of this variable.
         */
        [[nodiscard]] lang::Location typeLocation() const;

        /**
         * Get whether this variable is defined as final.
         */
        [[nodiscard]] bool isFinal() const;

        virtual void expand();
        void         setType(lang::ResolvingHandle<lang::Type> type);
        virtual void determineFlow();
        virtual void validateFlow(ValidationLogger& validation_logger) const;
        virtual void resolve();
        virtual void postResolve();
        virtual void createNativeBacking(CompileContext& context);
        virtual void build(CompileContext& context);

        [[nodiscard]] virtual std::vector<lang::ResolvingHandle<lang::Variable>> getVariableDependencies();
        [[nodiscard]] virtual std::vector<lang::ResolvingHandle<lang::Function>> getFunctionDependencies();

        /**
         * Validate this variable declaration.
         * @param validation_logger The logger to use for validation.
         */
        virtual void validate(ValidationLogger& validation_logger) const = 0;

        virtual void buildDeclaration(CompileContext& context)  = 0;
        virtual void buildDefinition(CompileContext& context)   = 0;
        virtual void buildFinalization(CompileContext& context) = 0;

        virtual Shared<lang::Value> getValue(CompileContext& context) = 0;
        virtual void                setValue(Shared<lang::Value> value, CompileContext& context);

        ~VariableDefinition() override = default;

      protected:
        virtual void                          storeValue(Shared<lang::Value> value, CompileContext& context) = 0;
        lang::ResolvingHandle<lang::Variable> self();
        [[nodiscard]] lang::Variable const&   self() const;

      private:
        lang::ResolvingHandle<lang::Variable> self_;

        lang::ResolvingHandle<lang::Type> type_;
        lang::Location                    type_location_;
        lang::Scope&                      scope_;
        bool                              is_final_;
        lang::Location                    location_;
    };
}

#endif
