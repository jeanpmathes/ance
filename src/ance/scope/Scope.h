#ifndef ANCE_SRC_ANCE_SCOPE_SCOPE_H_
#define ANCE_SRC_ANCE_SCOPE_SCOPE_H_

#include <map>
#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/Element.h"

#include "ance/AccessModifier.h"

namespace ance
{
    class Constant;
    class Function;
    class Value;
    class GlobalScope;
    class Variable;
    class Type;
}

class Statement;
class CompileContext;
class ValidationLogger;

namespace ance
{
    /**
     * The base class for scopes, which contain variables and functions.
     */
    class Scope : public virtual ance::Element
    {
      public:
        /**
         * Get the global scope.
         * @return The global scope.
         */
        virtual ance::GlobalScope* getGlobalScope() = 0;
        /**
         * Get the debug scope for this scope.
         * @param context The current compile context.
         * @return The debug scope.
         */
        virtual llvm::DIScope* getDebugScope(CompileContext* context) = 0;

        /**
         * Validate this scope.
         * @param validation_logger A logger to log validation messages to.
         */
        virtual void validate(ValidationLogger& validation_logger) = 0;

        /**
         * Get a variable by name.
         * @param identifier The identifier of the variable.
         * @return The variable with the name.
         */
        virtual ance::Variable* getVariable(std::string identifier) = 0;

        /**
         * Check if a type is registered in this scope.
         * @param type_name The name of the type.
         * @return True if it is registered.
         */
        virtual bool isTypeRegistered(const std::string& type_name) = 0;
        /**
         * Get a type by name.
         * @param type_name The name of the type.
         * @return The type with the given name.
         */
        virtual ance::Type* getType(const std::string& type_name) = 0;
        /**
         * Register a type in this scope.
         * @param type The type to register.
         */
        virtual void registerType(ance::Type* type) = 0;

        virtual ~Scope() = default;
    };
}
#endif