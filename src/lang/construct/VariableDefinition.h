#ifndef ANCE_SRC_LANG_CONSTRUCT_VARIABLEDEFINITION_H_
#define ANCE_SRC_LANG_CONSTRUCT_VARIABLEDEFINITION_H_

#include "lang/Element.h"
#include "lang/construct/value/Value.h"
#include "lang/utility/Location.h"

namespace lang
{
    class Scope;
    class Type;
    class Variable;
}

class ValidationLogger;
class CompileContext;

namespace lang
{
    /**
     * Defines the behaviour of a variable.
     */
    class VariableDefinition
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
        [[nodiscard]] lang::Scope& scope();

        /**
         * Get the scope in which this variable is defined.
         */
        [[nodiscard]] lang::Scope const& scope() const;

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
         * Get whether this variable is defined as final.
         */
        [[nodiscard]] bool isFinal() const;

        virtual void buildDeclaration(CompileContext& context)    = 0;
        virtual void buildInitialization(CompileContext& context) = 0;
        virtual void buildFinalization(CompileContext& context)   = 0;

        virtual Shared<lang::Value> getValuePointer(CompileContext& context) = 0;
        Shared<lang::Value>         getValue(CompileContext& context);
        virtual void                setValue(Shared<lang::Value> value, CompileContext& context);

        virtual ~VariableDefinition() = default;

      protected:
        virtual void                          storeValue(Shared<lang::Value> value, CompileContext& context) = 0;
        lang::ResolvingHandle<lang::Variable> self();
        [[nodiscard]] lang::Variable const&   self() const;

      private:
        lang::ResolvingHandle<lang::Variable> self_;

        lang::Location                    type_location_;
        lang::Scope&                      scope_;
        bool                              is_final_;
        lang::Location                    location_;
    };
}

#endif
