#ifndef ANCE_SRC_LANG_CONSTRUCT_VARIABLEDEFINITION_H_
#define ANCE_SRC_LANG_CONSTRUCT_VARIABLEDEFINITION_H_

#include "lang/Element.h"

#include "lang/construct/Value.h"
#include "lang/utility/Location.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Scope;
    class Type;
    class Variable;
}

class ValidationLogger;
class Execution;

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

        virtual void registerDeclaration(Execution& exec) const   = 0;
        virtual void registerDefinition(Execution& exec) const    = 0;
        virtual void performInitialization(Execution& exec) const = 0;
        virtual void performFinalization(Execution& exec) const   = 0;

        virtual Shared<lang::Value> getValuePointer(Execution& exec) const = 0;

        lang::ResolvingHandle<lang::Variable> self();
        [[nodiscard]] lang::Variable const&   self() const;

        virtual ~VariableDefinition() = default;

      private:
        lang::ResolvingHandle<lang::Variable> self_;

        lang::Location type_location_;
        lang::Scope&   scope_;
        bool           is_final_;
        lang::Location location_;
    };
}

#endif
