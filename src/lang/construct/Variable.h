#ifndef ANCE_SRC_LANG_CONSTRUCT_VARIABLE_H_
#define ANCE_SRC_LANG_CONSTRUCT_VARIABLE_H_

#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>

#include "lang/AccessModifier.h"
#include "lang/Element.h"
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

class ConstantExpression;
class CompileContext;
class ValidationLogger;

namespace lang
{
    /**
     * The base class of all variables.
     */
    class Variable
        : public HandleTarget<lang::Variable>
        , public lang::Element<Variable, ANCE_CONSTRUCTS>
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
        [[nodiscard]] bool isDefined() const;

        /**
         * Define this variable as a global variable.
         * @param type The type, if there is one.
         * @param type_location The location of the type.
         * @param containing_scope The containing scope.
         * @param access The access modifier.
         * @param init The expression used for initialization.
         * @param is_final Whether the variable is final.
         * @param is_constant Whether the variable is constant.
         * @param location The source location.
         */
        void defineAsGlobal(std::optional<lang::ResolvingHandle<lang::Type>> type,
                            lang::Location                                   type_location,
                            GlobalScope&                                     containing_scope,
                            lang::AccessModifier                             access,
                            std::unique_ptr<Expression>                      init,
                            bool                                             is_final,
                            bool                                             is_constant,
                            lang::Location                                   location);

        /**
         * Define this variable as a local variable.
         * @param type The type.
         * @param type_location The location of the type.
         * @param containing_scope The containing scope.
         * @param is_final Whether the variable is final.
         * @param value The initial value.
         * @param parameter_no The parameter number. Use zero if this is not a parameter.
         * @param location The source location.
         */
        void defineAsLocal(lang::ResolvingHandle<lang::Type>   type,
                           lang::Location                      type_location,
                           Scope&                              containing_scope,
                           bool                                is_final,
                           std::shared_ptr<lang::Value> const& value,
                           unsigned                            parameter_no,
                           lang::Location                      location);

        /**
         * Get the name.
         * @return The name.
         */
        [[nodiscard]] Identifier const& name() const;
        /**
         * Get the containing scope.
         * @return The scope.
         */
        [[nodiscard]] lang::Scope* scope() const;
        /**
         * Get the value type.
         * @return The type.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Type> type() const;
        /**
         * Get whether this variable is final.
         * @return Whether it is final.
         */
        [[nodiscard]] bool isFinal() const;

        /**
         * Validate this variable.
         * @param validation_logger A logger to log validation messages.
         */
        void validate(ValidationLogger& validation_logger) const;

        /**
         * Build the variable declaration which prepares the storage.
         * @param context The current compile context.
         */
        void buildDeclaration(CompileContext& context);

        /**
         * Build the variable definition which initializes the storage.
         * @param context The current compile context.
         */
        void buildDefinition(CompileContext& context);

        /**
         * Build the variable finalizer which cleans up the storage.
         * @param context The current compile context.
         */
        void buildFinalization(CompileContext& context);

        /**
         * Validate getting a value.
         * @param validation_logger A validation logger to log messages.
         * @param location The source location.
         * @return True if getting the value is valid.
         */
        bool validateGetValue(ValidationLogger& validation_logger, lang::Location location) const;

        /**
         * Validate setting a value.
         * @param value The value to set.
         * @param validation_logger A logger to log validation messages.
         * @param assignable_location The source location of the assignable.
         * @param assigned_location The source location of the value that is assigned to the assignable.
         */
        bool validateSetValue(std::shared_ptr<lang::Value> const& value,
                              ValidationLogger&                   validation_logger,
                              lang::Location                      assignable_location,
                              lang::Location                      assigned_location) const;

        /**
         * Get the current value of the variable.
         * @param context The current compile context.
         * @return The current value.
         */
        std::shared_ptr<lang::Value> getValue(CompileContext& context);
        /**
         * Set the current value of the variable.
         * @param value The new value.
         * @param context The current compile context.
         */
        void setValue(std::shared_ptr<Value> value, CompileContext& context);

        /**
         * Get the variable dependencies of this variable. Only variables in unordered scope have dependencies.
         * @return The dependencies.
         */
        [[nodiscard]] std::set<lang::ResolvingHandle<lang::Variable>> getVariableDependencies() const;

        /**
         * Get the function dependencies of this variable. Only variables in unordered scope have dependencies.
         * @return The dependencies.
         */
        [[nodiscard]] std::set<lang::ResolvingHandle<lang::Function>> getFunctionDependencies() const;

        /**
         * Get an undefined variable with the same name.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Variable> toUndefined() const;

        // These methods are required by global variables for their initialization function.
        void expand();
        void determineFlow();
        void validateFlow(ValidationLogger& validation_logger) const;
        void resolve();
        void postResolve();
        void createNativeBacking(CompileContext& context);
        void build(CompileContext& context);

      private:
        lang::Identifier                          name_;
        std::unique_ptr<lang::VariableDefinition> definition_ {};
    };
}
#endif
