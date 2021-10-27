#ifndef ANCE_SRC_ANCE_CONSTRUCT_VARIABLE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_VARIABLE_H_

#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>

#include "ance/AccessModifier.h"
#include "ance/construct/VariableDefinition.h"
#include "ance/utility/Location.h"

namespace ance
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

namespace ance
{
    /**
     * The base class of all variables.
     */
    class Variable
    {
      public:
        /**
         * Create an undefined variable.
         * @param identifier The identifier.
         */
        explicit Variable(std::string identifier);

        /**
         * Check if this variable is defined.
         * @return Whether it is defined.
         */
        [[nodiscard]] bool isDefined() const;

        /**
         * Define this variable as a global variable.
         * @param type The type.
         * @param containing_scope The containing scope.
         * @param access The access modifier.
         * @param constant_init The constant used for initialization.
         * @param is_final Whether the variable is final.
         * @param is_constant Whether the variable is constant.
         * @param location The source location.
         */
        void defineAsGlobal(ance::Type*         type,
                            ance::GlobalScope*  containing_scope,
                            AccessModifier      access,
                            ConstantExpression* constant_init,
                            bool                is_final,
                            bool                is_constant,
                            ance::Location      location);

        /**
         * Define this variable as a local variable.
         * @param type The type.
         * @param containing_scope The containing scope.
         * @param is_final Whether the variable is final.
         * @param value The initial value.
         * @param parameter_no The parameter number. Use zero if this is not a parameter.
         * @param location The source location.
         */
        void defineAsLocal(ance::Type*                         type,
                           ance::LocalScope*                   containing_scope,
                           bool                                is_final,
                           const std::shared_ptr<ance::Value>& value,
                           unsigned                            parameter_no,
                           ance::Location                      location);

        /**
         * Get the identifier.
         * @return The identifier.
         */
        [[nodiscard]] const std::string& identifier() const;
        /**
         * Get the containing scope.
         * @return The scope.
         */
        [[nodiscard]] ance::Scope* scope() const;
        /**
         * Get the value type.
         * @return The type.
         */
        [[nodiscard]] ance::Type* type() const;
        /**
         * Get whether this variable is final.
         * @return Whether it is final.
         */
        [[nodiscard]] bool isFinal() const;

        /**
         * Validate this variable.
         * @param validation_logger A logger to log validation messages.
         */
        void validate(ValidationLogger& validation_logger);

        /**
         * Build the variable declaration which prepares the storage.
         * @param context The current compile context.
         */
        void buildDeclaration(CompileContext* context);

        /**
         * Build the variable definition which initializes the storage.
         * @param context The current compile context.
         */
        void buildDefinition(CompileContext* context);

        /**
         * Validate getting a value.
         * @param validation_logger A validation logger to log messages.
         * @param location The source location.
         * @return True if getting the value is valid.
         */
        bool validateGetValue(ValidationLogger& validation_logger, ance::Location location) const;

        /**
         * Validate setting a value.
         * @param value The value to set.
         * @param validation_logger A logger to log validation messages.
         * @param assignable_location The source location of the assignable.
         * @param assigned_location The source location of the value that is assigned to the assignable.
         */
        void validateSetValue(const std::shared_ptr<ance::Value>& value,
                              ValidationLogger&                   validation_logger,
                              ance::Location                      assignable_location,
                              ance::Location                      assigned_location) const;

        /**
         * Get the current value of the variable.
         * @param context The current compile context.
         * @return The current value.
         */
        std::shared_ptr<ance::Value> getValue(CompileContext* context);
        /**
         * Set the current value of the variable.
         * @param value The new value.
         * @param context The current compile context.
         */
        void setValue(const std::shared_ptr<ance::Value>& value, CompileContext* context);

      private:
        std::string                               identifier_;
        std::unique_ptr<ance::VariableDefinition> definition_ {};
    };
}
#endif