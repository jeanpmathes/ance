#ifndef ANCE_SRC_ANCE_SCOPE_SCOPE_H_
#define ANCE_SRC_ANCE_SCOPE_SCOPE_H_

#include <map>
#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/AccessModifier.h"
#include "ance/utility/Location.h"
#include "ance/utility/ResolvingHandle.h"

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
    class Scope
    {
      public:
        /**
         * Get the containing scope or the global scope if there is no containing scope.
         * @return The containing scope.
         */
        virtual ance::Scope* scope() = 0;

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
         * Register the usage of a variable in this scope. Only variables that are registered will be resolved.
         * @param variable The variable to register and resolve. A variable can be registered multiple times, but must be undefined.
         */
        virtual void registerUsage(ance::ResolvingHandle<ance::Variable> variable) = 0;

        /**
         * Register the usage of a function in this scope. Only functions that are registered will be resolved.
         * @param function The function to register and resolve. A function can be registered multiple times, but must be undefined.
         */
        virtual void registerUsage(ance::ResolvingHandle<ance::Function> function) = 0;

        /**
         * Register the usage of a type in this scope. Only types that are registered will be resolved.
         * @param type The type to register and resolve. A type can be registered multiple times, but must be undefined.
         */
        virtual void registerUsage(ance::ResolvingHandle<ance::Type> type) = 0;

        /**
         * Add the definition for a type. A scope can ignore definitions.
         * @param type The type to define.
         */
        virtual void registerDefinition(ance::ResolvingHandle<ance::Type> type) = 0;

        /**
         * Add a type to this scope. Undefined types will be resolved.
         * @param type The type to add.
         */
        void addType(ance::ResolvingHandle<ance::Type> type);

        /**
         * Resolve all undefined usages to find their definitions.
         */
        virtual void resolve() = 0;

        /**
         * Resolve the definition of a function.
         * @param function The function to find a definition for.
         * @return True if a definition was found.
         */
        virtual bool resolveDefinition(ance::ResolvingHandle<ance::Function> function) = 0;

        /**
         * Resolve the definition of a variable.
         * @param variable The variable to find a definition for.
         * @return True if a definition was found.
         */
        virtual bool resolveDefinition(ance::ResolvingHandle<ance::Variable> variable) = 0;

        /**
         * Resolve the definition of a type.
         * @param type The type to find a definition for.
         * @return True if a definition was found.
         */
        virtual bool resolveDefinition(ance::ResolvingHandle<ance::Type> type) = 0;

        /**
         * Validate this scope.
         * @param validation_logger A logger to log validation messages to.
         */
        virtual void validate(ValidationLogger& validation_logger) = 0;

        virtual ~Scope() = default;
    };
}
#endif