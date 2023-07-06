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
#include "lang/utility/OwningHandle.h"
#include "lang/utility/ResolvingHandle.h"

namespace lang
{
    class Constant;
    class Function;
    class FunctionGroup;
    class Value;
    class GlobalScope;
    class OrderedScope;
    class LocalScope;
    class Variable;
    class Type;
    class Context;
    class Identifier;
    class Description;
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
      protected:
        /**
         * Creates a new scope without a parent scope.
         * If this is used, the getters must be overridden.
         */
        explicit Scope();

        /**
         * Creates a new scope with a parent scope.
         * @param containing_scope The parent scope.
         */
        explicit Scope(lang::Scope* containing_scope);

      public:
        /**
         * Get the containing scope or the global scope if there is no containing scope.
         * @return The containing scope.
         */
        virtual lang::Scope* scope();

        /**
         * Get the containing scope or the global scope if there is no containing scope.
         * @return The containing scope.
         */
        [[nodiscard]] virtual lang::Scope const* scope() const;

        /**
         * Get the global scope.
         * @return The global scope.
         */
        virtual lang::GlobalScope* getGlobalScope();

        /**
         * Get the global scope.
         * @return The global scope.
         */
        [[nodiscard]] virtual lang::GlobalScope const* getGlobalScope() const;

        /**
         * Get this scope as an ordered scope.
         * @return An ordered scope, or nullptr if this scope is not an ordered scope.
         */
        virtual lang::OrderedScope* asOrderedScope();

        /**
         * Get the context the global scope is in.
         */
        virtual lang::Context& context();

        /**
         * Get the context the global scope is in.
         */
        [[nodiscard]] virtual lang::Context const& context() const;

        /**
         * Whether this scope is part of a function.
         */
        [[nodiscard]] virtual bool isPartOfFunction() const = 0;

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
        Owned<lang::OrderedScope> makeLocalScope();

        /**
         * Whether a name is conflicted in this scope, meaning there are multiple elements with the same name.
         * @param name The name to check.
         * @return True if the name is conflicted, false otherwise.
         */
        [[nodiscard]] virtual bool isNameConflicted(lang::Identifier const& name) const = 0;

        /**
         * Add an description element to this scope.
         * @param description The description to add.
         */
        virtual void addDescription(Owned<lang::Description> description) = 0;

        /**
         * Add a function to this scope.
         * @param function The function to add.
         */
        virtual void addFunction(lang::OwningHandle<lang::Function> function) = 0;

        /**
         * Add a variable to this scope.
         * @param variable The variable to add.
         */
        virtual void addVariable(lang::OwningHandle<lang::Variable> variable) = 0;

        /**
         * Add a type to this scope.
         * @param type The type to add.
         */
        virtual void addType(lang::OwningHandle<lang::Type> type) = 0;

        /**
         * Register the usage of a variable in this scope. Only variables that are registered will be resolved.
         * @param variable The variable to register and resolve. A variable can be registered multiple times, but must be undefined.
         */
        void registerUsage(lang::ResolvingHandle<lang::Variable> variable);

        /**
         * Register the usage of a function group in this scope. Only function groups that are registered will be resolved.
         * @param function The function group to register and resolve. A function group can be registered multiple times, but must be undefined.
         */
        void registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function);

        /**
         * Register the usage of a type in this scope. Only types that are registered will be resolved.
         * @param type The type to register and resolve. A type can be registered multiple times, but must be undefined.
         */
        void registerUsage(lang::ResolvingHandle<lang::Type> type);

      protected:
        virtual void onRegisterUsage(lang::ResolvingHandle<lang::Variable> variable)      = 0;
        virtual void onRegisterUsage(lang::ResolvingHandle<lang::FunctionGroup> function) = 0;
        virtual void onRegisterUsage(lang::ResolvingHandle<lang::Type> type)              = 0;

      public:
        /**
         * Add the definition for a type. A scope can ignore definitions.
         * @param type The type to define.
         */
        virtual void registerDefinition(lang::ResolvingHandle<lang::Type> type) = 0;

        /**
         * Add a type to this scope. Undefined types will be resolved.
         * @param type The type to add.
         */
        void registerUsageIfUndefined(lang::ResolvingHandle<lang::Type> type);

        /**
         * Connect a given variable with a fitting definition, following the definition order.
         * Only ordered scopes will connect variables.
         * @return If no connection was possible or the scope is not ordered, the variable is returned.
         */
        virtual Optional<OwningHandle<lang::Variable>> connectWithDefinitionAccordingToOrdering(
            lang::OwningHandle<lang::Variable> variable);

        /**
         * Resolve all undefined usages to find their definitions.
         */
        virtual void resolve() = 0;

        /**
         * Perform operations that require resolved definitions and have to be done before validation.
         */
        virtual void postResolve();

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
         * Add a dependency to a function.
         * @param function The function to add a dependency to.
         */
        void addDependency(lang::ResolvingHandle<lang::Function> function);

      private:
        void addDependency(lang::ResolvingHandle<lang::Variable> variable);
        void addDependency(lang::ResolvingHandle<lang::FunctionGroup> function);
        void addDependency(lang::ResolvingHandle<lang::Type> type);

      public:
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

        /**
         * Get the function group dependencies.
         * @return The function group dependencies.
         */
        std::vector<lang::ResolvingHandle<lang::FunctionGroup>> getFunctionGroupDependencies();

        /**
         * Get the type dependencies.
         * @return The type dependencies.
         */
        std::vector<lang::ResolvingHandle<lang::Type>> getTypeDependencies();

        ~Scope() override = default;

      protected:
        virtual void onSubScope(Scope* sub_scope);

      private:
        lang::Scope* containing_scope_  = nullptr;
        size_t       temp_name_counter_ = 0;

        std::vector<lang::ResolvingHandle<lang::Variable>>      used_variables_;
        std::vector<lang::ResolvingHandle<lang::FunctionGroup>> used_function_groups_;
        std::vector<lang::ResolvingHandle<lang::Type>>          used_types_;

        std::vector<VariableDependency>                         variable_dependencies_;
        std::map<lang::ResolvingHandle<lang::Variable>, size_t> variable_to_dependency_index_;

        std::vector<lang::ResolvingHandle<lang::Function>> function_dependencies_;
        std::set<lang::ResolvingHandle<lang::Function>>    function_dependencies_set_;

        std::vector<lang::ResolvingHandle<lang::FunctionGroup>> function_group_dependencies_;
        std::set<lang::ResolvingHandle<lang::FunctionGroup>>    function_group_dependencies_set_;

        std::vector<lang::ResolvingHandle<lang::Type>> type_dependencies_;
        std::set<lang::ResolvingHandle<lang::Type>>    type_dependencies_set_;
    };
}
#endif
