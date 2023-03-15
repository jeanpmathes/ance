#ifndef ANCE_SRC_LANG_SCOPE_SCOPE_H_
#define ANCE_SRC_LANG_SCOPE_SCOPE_H_

#include <map>
#include <string>
#include <utility>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/AccessModifier.h"
#include "lang/Element.h"
#include "lang/utility/Location.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Constant;
    class Function;
    class FunctionGroup;
    class Value;
    class GlobalScope;
    class LocalScope;
    class Variable;
    class Type;
    class Context;
}

class Statement;
class CompileContext;
class ValidationLogger;

namespace lang
{
    /**
     * The base class for scopes, which contain variables and functions.
     */
    class Scope : public virtual lang::Visitable<ANCE_CONSTRUCTS>
    {
      public:
        /**
         * Get the containing scope or the global scope if there is no containing scope.
         * @return The containing scope.
         */
        virtual lang::Scope* scope() = 0;

        /**
         * Get the global scope.
         * @return The global scope.
         */
        virtual lang::GlobalScope* getGlobalScope() = 0;

        /**
         * Get the context the global scope is in.
         */
        virtual lang::Context& context();

        /**
         * Get the context the global scope is in.
         */
        virtual lang::Context const& context() const;

        /**
         * Get the global scope.
         * @return The global scope.
         */
        [[nodiscard]] virtual lang::GlobalScope const* getGlobalScope() const = 0;

        /**
         * Get this scope as a local scope, if it is one.
         * @return The local scope, or nullptr if this scope is not a local scope.
         */
        virtual lang::LocalScope* asLocalScope();

        /**
         * Get the name for a temporary element like a variable or function.
         * @return A name that that will not clash with any other element in this scope.
         */
        std::string getTemporaryName();

        /**
         * Get the debug scope for this scope.
         * @param context The current compile context.
         * @return The debug scope.
         */
        virtual llvm::DIScope* getDebugScope(CompileContext& context) const = 0;

        /**
         * Create a local scope in this scope.
         * @return The created local scope.
         */
        Owned<lang::LocalScope> makeLocalScope();

        /**
         * Register the usage of a variable in this scope. Only variables that are registered will be resolved.
         * @param variable The variable to register and resolve. A variable can be registered multiple times, but must be undefined.
         */
        virtual void registerUsage(lang::ResolvingHandle<lang::Variable> variable) = 0;

        /**
         * Register the usage of a function group in this scope. Only function groups that are registered will be resolved.
         * @param function The function group to register and resolve. A function group can be registered multiple times, but must be undefined.
         */
        virtual void registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function) = 0;

        /**
         * Register the usage of a type in this scope. Only types that are registered will be resolved.
         * @param type The type to register and resolve. A type can be registered multiple times, but must be undefined.
         */
        virtual void registerUsage(lang::ResolvingHandle<lang::Type> type) = 0;

        /**
         * Add the definition for a type. A scope can ignore definitions.
         * @param type The type to define.
         */
        virtual void registerDefinition(lang::ResolvingHandle<lang::Type> type) = 0;

        /**
         * Add a type to this scope. Undefined types will be resolved.
         * @param type The type to add.
         */
        void addType(lang::ResolvingHandle<lang::Type> type);

        /**
         * Resolve all undefined usages to find their definitions.
         */
        virtual void resolve() = 0;

        /**
         * Perform operations that require resolved definitions and have to be done before validation.
         */
        virtual void postResolve() = 0;

        /**
         * Resolve the definition of a function group.
         * @param function The function group to find a definition for.
         * @return True if a definition was found.
         */
        virtual bool resolveDefinition(lang::ResolvingHandle<lang::FunctionGroup> function) = 0;

        /**
         * Resolve the definition of a variable.
         * @param variable The variable to find a definition for.
         * @return True if a definition was found.
         */
        virtual bool resolveDefinition(lang::ResolvingHandle<lang::Variable> variable) = 0;

        /**
         * Resolve the definition of a type.
         * @param type The type to find a definition for.
         * @return True if a definition was found.
         */
        virtual bool resolveDefinition(lang::ResolvingHandle<lang::Type> type) = 0;

        /**
         * Build the finalization for all entities in this scope.
         * @param context The current compile context.
         */
        virtual void buildFinalization(CompileContext& context) = 0;

        /**
         * Add a dependency on a variable.
         * @param variable The variable to add a dependency on. Must be defined.
         */
        void addDependency(lang::ResolvingHandle<lang::Variable> variable);

        /**
         * Add a dependency on a function.
         * @param function The function to add a dependency on. Must be defined.
         */
        void addDependency(lang::ResolvingHandle<lang::Function> function);

        struct VariableDependency {
            explicit VariableDependency(lang::ResolvingHandle<lang::Variable> var) : variable(std::move(var)) {}
            VariableDependency(VariableDependency& other)  = default;
            VariableDependency(VariableDependency&& other) = default;

            lang::ResolvingHandle<lang::Variable> variable;
            size_t                                count {0};
        };

        /**
         * Get the variable dependencies and their count.
         * @return The variable dependencies.
         */
        std::vector<VariableDependency> getVariableDependencies();

        /**
         * Get the function dependencies.
         * @return The function dependencies.
         */
        std::vector<lang::ResolvingHandle<lang::Function>> getFunctionDependencies();

        ~Scope() override = default;

      protected:
        virtual void onSubScope(LocalScope* local_scope);

      private:
        size_t temp_name_counter_ = 0;

        std::vector<VariableDependency>                         variable_dependencies_;
        std::map<lang::ResolvingHandle<lang::Variable>, size_t> variable_to_dependency_index_;

        std::vector<lang::ResolvingHandle<lang::Function>> function_dependencies_;
        std::set<lang::ResolvingHandle<lang::Function>>    function_dependencies_set_;
    };
}
#endif
