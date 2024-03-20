#ifndef ANCE_SRC_LANG_CONSTRUCT_VARIABLE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VARIABLE_H_

#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>

#include "lang/Element.h"
#include "lang/construct/Entity.h"

#include "lang/AccessModifier.h"
#include "lang/Assigner.h"
#include "lang/construct/GlobalVariable.h"
#include "lang/construct/VariableDefinition.h"
#include "lang/utility/Identifier.h"
#include "lang/utility/Location.h"

namespace lang
{
    class Scope;
    class GlobalScope;
    class LocalScope;

    class Type;
    class Value;
}

class LiteralExpression;
class CompileContext;
class ValidationLogger;

namespace lang
{
    /**
     * The base class of all variables.
     */
    class Variable
        : public HandleTarget<lang::Variable>
        , public Entity
    {
      public:
        /**
         * Create an undefined variable.
         * @param name The name.
         */
        explicit Variable(lang::Identifier name);

        /**
         * Check if this variable is defined.
         * @return Whether it is defined.
         */
        [[nodiscard]] bool isDefined() const override;

        /**
         * Define this variable as a global variable.
         * @param type The type, if there is one.
         * @param type_location The location of the type.
         * @param containing_scope The containing scope.
         * @param access The access modifier.
         * @param is_import Whether the variable is imported.
         * @param init The expression or function used for initialization.
         * @param assigner The assigner used for initialization.
         * @param is_constant Whether the variable is constant.
         * @param location The source location.
         * @return The global variable.
         */
        lang::GlobalVariable* defineAsGlobal(lang::ResolvingHandle<lang::Type> type,
                                             lang::Location                    type_location,
                                             Scope&                            containing_scope,
                                             lang::AccessModifier              access,
                                             bool                              is_import,
                                             lang::GlobalInitializer           init,
                                             lang::Assigner                    assigner,
                                             bool                              is_constant,
                                             lang::Location                    location);

        /**
         * Define this variable as a local variable.
         * @param type The type.
         * @param type_location The location of the type.
         * @param containing_scope The containing scope.
         * @param is_final Whether the variable is final.
         * @param init The initial provider.
         * @param parameter_index The index of the parameter, if this is a parameter.
         * @param location The source location.
         */
        void defineAsLocal(lang::ResolvingHandle<lang::Type> type,
                           lang::Location                    type_location,
                           Scope&                            containing_scope,
                           bool                              is_final,
                           lang::LocalInitializer const&     init,
                           Optional<size_t> const&           parameter_index,
                           lang::Location                    location);

        /**
         * Get the name.
         * @return The name.
         */
        [[nodiscard]] Identifier const& name() const override;
        /**
         * Get the containing scope.
         * @return The scope.
         */
        [[nodiscard]] lang::Scope& scope() override;
        /**
         * Get the containing scope.
         * @return The scope.
         */
        [[nodiscard]] lang::Scope const& scope() const override;
        /**
         * Get the value type.
         * @return The type.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Type> type();
        /**
         * Get the value type.
         * @return The type.
         */
        [[nodiscard]] lang::Type const& type() const;
        /**
         * Get the target type, meaning the type of value that is required when assigning to this variable.
         * @return The target type.
         */
        [[nodiscard]] lang::Type const& targetType() const;
        /**
         * Get whether this variable is final.
         * @return Whether it is final.
         */
        [[nodiscard]] bool isFinal() const;

        /**
         * Build the variable declaration which prepares the storage.
         * @param context The current compile context.
         */
        void buildDeclaration(CompileContext& context) const;

        /**
         * Build the variable initialization which initializes the storage.
         * @param context The current compile context.
         */
        void buildInitialization(CompileContext& context) const;

        /**
         * Build the variable finalizer which cleans up the storage.
         * @param context The current compile context.
         */
        void buildFinalization(CompileContext& context) const;

        /**
         * Validate getting a value.
         * @param validation_logger A validation logger to log messages.
         * @param location The source location.
         * @return True if getting the value is valid.
         */
        bool validateGetValue(ValidationLogger& validation_logger, lang::Location location) const;

        /**
         * Validate setting a value.
         * @param value_type The type of the value that is assigned.
         * @param validation_logger A logger to log validation messages.
         * @param assignable_location The source location of the assignable.
         * @param assigned_location The source location of the value that is assigned to the assignable.
         */
        bool validateSetValue(lang::Type const& value_type,
                              ValidationLogger& validation_logger,
                              lang::Location    assignable_location,
                              lang::Location    assigned_location) const;

        /**
         * Get a pointer to the current value of the variable.
         * @param context The current compile context.
         * @return A pointer to the value.
         */
        Shared<lang::Value> getValuePointer(CompileContext& context) const;

        /**
         * Get the current value of the variable.
         * @param context The current compile context.
         * @return The value.
         */
        Shared<lang::Value> getValue(CompileContext& context) const;

        /**
         * Get an undefined variable with the same name.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Variable> toUndefined() const;

        ResolvingHandle<lang::Entity> getUndefinedClone(Context& new_context) const override;

      private:
        lang::Identifier                          name_;
        lang::ResolvingHandle<lang::Type>         type_;
        Optional<Owned<lang::VariableDefinition>> definition_ {};
    };
}
#endif
