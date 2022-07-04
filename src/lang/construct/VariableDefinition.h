#ifndef ANCE_SRC_LANG_CONSTRUCT_VARIABLEDEFINITION_H_
#define ANCE_SRC_LANG_CONSTRUCT_VARIABLEDEFINITION_H_

#include "lang/construct/value/Value.h"
#include "lang/utility/Location.h"
#include "lang/Element.h"

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
        VariableDefinition(Identifier                        name,
                           lang::ResolvingHandle<lang::Type> type,
                           lang::Location                    type_location,
                           Scope&                            containing_scope,
                           bool                              is_final,
                           lang::Location                    location);

        [[nodiscard]] const Identifier& name() const;

        /**
         * Get the scope in which this variable is defined.
         */
        [[nodiscard]] lang::Scope* scope() const;

        /**
         * Get the type of this variable.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Type> type() const;

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

        /**
         * Validate this variable declaration.
         * @param validation_logger The logger to use for validation.
         */
        virtual void validate(ValidationLogger& validation_logger) const = 0;

        virtual void buildDeclaration(CompileContext* context) = 0;
        virtual void buildDefinition(CompileContext* context)  = 0;

        virtual std::shared_ptr<lang::Value> getValue(CompileContext* context) = 0;
        virtual void                         setValue(std::shared_ptr<lang::Value> value, CompileContext* context);

        ~VariableDefinition() override = default;

      protected:
        virtual void storeValue(std::shared_ptr<lang::Value> value, CompileContext* context) = 0;

      private:
        lang::Identifier name_;

        lang::ResolvingHandle<lang::Type> type_;
        lang::Location                    type_location_;
        lang::Scope&                      scope_;
        bool                              is_final_;
        lang::Location                    location_;
    };
}

#endif