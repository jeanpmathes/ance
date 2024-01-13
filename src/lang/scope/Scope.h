#ifndef ANCE_SRC_LANG_SCOPE_SCOPE_H_
#define ANCE_SRC_LANG_SCOPE_SCOPE_H_

#include <map>
#include <string>
#include <utility>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "compiler/Execution.h"
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
         * If this is used, the getters must be overridden or setContainingScope must be called.
         */
        explicit Scope();

        /**
         * Creates a new scope with a parent scope.
         * @param containing_scope The parent scope.
         */
        explicit Scope(lang::Scope* containing_scope);

      public:
        void setContainingScope(lang::Scope& containing_scope);

        /**
         * Get the containing scope or the global scope if there is no containing scope.
         * @return The containing scope.
         */
        virtual lang::Scope& scope();

        /**
         * Get the containing scope or the global scope if there is no containing scope.
         * @return The containing scope.
         */
        [[nodiscard]] virtual lang::Scope const& scope() const;

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
         * Get this scope as an ordered scope.
         * @return An ordered scope, or nullptr if this scope is not an ordered scope.
         */
        [[nodiscard]] lang::OrderedScope const* asOrderedScope() const;

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
        [[nodiscard]] std::string getTemporaryName() const;

        /**
         * Get the debug scope for this scope.
         * @param context The current compile context.
         * @return The debug scope.
         */
        virtual Execution::Scoped getDebugScope(CompileContext& context) const = 0;

        /**
         * Create a local scope in this scope.
         * @param code_block The code block containing the local scope.
         * @return The created local scope.
         */
        Owned<lang::OrderedScope> makeLocalScope(lang::CodeBlock& code_block);

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
         * Add an entity to this scope.
         * @param entity The entity to add.
         */
        virtual void addEntity(lang::OwningHandle<lang::Entity> entity) = 0;

        /**
         * Register the usage of a entity in this scope. Only entity that are registered will be resolved.
         * @param entity The entity to register and resolve. An entity can be registered multiple times.
         * @param is_only_declared Whether a declaration is sufficient or a definition is required.
         */
        void registerUsage(lang::ResolvingHandle<lang::Entity> entity, bool is_only_declared = false);

      protected:
        virtual void onRegisterUsage(lang::ResolvingHandle<lang::Entity> entity) = 0;

      public:
        /**
         * Connect a given entity with a fitting definition, following the definition order.
         * Only ordered scopes will connect entities.
         * @return If no connection was possible or the scope is not ordered, the entity is returned.
         */
        virtual Optional<OwningHandle<lang::Entity>> connectWithDefinitionAccordingToOrdering(
            lang::OwningHandle<lang::Entity> variable);

        /**
         * Resolve all undefined usages to find their definitions.
         */
        virtual void resolve() = 0;

        /**
         * Perform operations that require resolved definitions and have to be done before validation.
         */
        virtual void postResolve();

        /**
         * Resolve the definition of an entity.
         * @param entity The entity to resolve.
         * @return True if a definition was found.
         */
        virtual bool resolveDefinition(lang::ResolvingHandle<lang::Entity> entity) = 0;

        /**
         * Build the declarations for all entities in this scope.
         * @param context The current compile context.
         */
        virtual void buildDeclarations(CompileContext& context) = 0;
        /**
         * Build the finalization for all entities in this scope.
         * @param context The current compile context.
         */
        virtual void buildFinalization(CompileContext& context) = 0;

      private:
        void addDependency(lang::ResolvingHandle<lang::Entity> entity, bool is_only_declared);

      public:
        template<typename Entity>
        struct Dependency {
            explicit Dependency(lang::ResolvingHandle<Entity> dep) : entity(std::move(dep)) {}
            Dependency(lang::ResolvingHandle<Entity> dep, size_t initial_count)
                : entity(std::move(dep))
                , count(initial_count)
            {}
            Dependency(Dependency& other)           = default;
            Dependency(Dependency&& other) noexcept = default;

            lang::ResolvingHandle<Entity> entity;
            size_t                        count {0};
        };

        /**
         * Get the dependencies on declarations of this scope and their count.
         * @return The dependencies.
         */
        std::vector<Dependency<lang::Entity>> getDependenciesOnDeclaration();
        /**
         * Get the dependencies on delcaraions of this scope and their count.
         * @return The dependencies.
         */
        [[nodiscard]] std::vector<std::reference_wrapper<lang::Entity const>> getDependenciesOnDeclaration() const;

        /**
         * Get the dependencies on definitions of this scope and their count.
         * @return The dependencies.
         */
        std::vector<Dependency<lang::Entity>> getDependenciesOnDefinition();
        /**
         * Get the dependencies on definitions of this scope and their count.
         * @return The dependencies.
         */
        [[nodiscard]] std::vector<std::reference_wrapper<lang::Entity const>> getDependenciesOnDefinition() const;

        ~Scope() override = default;

      private:
        lang::Scope* containing_scope_ = nullptr;

        std::vector<Dependency<lang::Entity>>                 entity_declaration_dependencies_;
        std::map<lang::ResolvingHandle<lang::Entity>, size_t> entity_to_declaration_dependency_index_;

        std::vector<Dependency<lang::Entity>>                 entity_definition_dependencies_;
        std::map<lang::ResolvingHandle<lang::Entity>, size_t> entity_to_definition_dependency_index_;
    };
}
#endif
