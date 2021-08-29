#ifndef ANCE_SRC_ANCE_CONSTRUCT_VARIABLE_H_
#define ANCE_SRC_ANCE_CONSTRUCT_VARIABLE_H_

#include <string>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>

#include "ance/utility/Location.h"

class CompileContext;

namespace llvm
{
    class DIBuilder;
    class LLVMContext;
}

namespace ance
{
    class Scope;
    class Type;
    class Value;

    /**
     * The base class of all variables.
     */
    class Variable
    {
      protected:
        /**
         * Create a new defined variable.
         * @param containing_scope The containing scope.
         * @param identifier The identifier.
         * @param type The value type.
         * @param is_final Whether the variable is final.
         */
        Variable(ance::Scope* containing_scope, std::string identifier, ance::Type* type, bool is_final);
        /**
         * Create an undefined variable.
         * @param identifier The identifier.
         */
        explicit Variable(std::string identifier);

        /**
         * Define this variable.
         * @param containing_scope The containing scope.
         * @param type The value type.
         * @param is_final Whether the variable is final.
         */
        void define(ance::Scope* containing_scope, ance::Type* type, bool is_final);

      public:
        /**
         * Check if this variable is defined.
         * @return Whether it is defined.
         */
        bool isDefined() const;

        /**
         * Validate this variable.
         */
        virtual void validate() = 0;

        /**
         * Get the identifier.
         * @return The identifier.
         */
        [[nodiscard]] std::string identifier() const;
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
         * Validate setting a value.
         * @param value The value to set.
         */
        void validateSetValue(ance::Value* value);

        /**
         * Get the current value of the variable.
         * @param context The current compile context.
         * @return The current value.
         */
        virtual ance::Value* getValue(CompileContext* context) = 0;
        /**
         * Set the current value of the variable.
         * @param value The new value.
         * @param context The current compile context.
         */
        virtual void setValue(ance::Value* value, CompileContext* context) = 0;

      private:
        std::string identifier_;
        bool        is_defined_;

        ance::Scope* scope_;
        ance::Type*  type_;
        bool         is_final_;
    };
}
#endif