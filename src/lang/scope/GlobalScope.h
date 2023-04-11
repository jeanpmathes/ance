#ifndef ANCE_SRC_LANG_SCOPE_GLOBALSCOPE_H_
#define ANCE_SRC_LANG_SCOPE_GLOBALSCOPE_H_

#include "Scope.h"

#include <optional>
#include <vector>

#include "lang/AccessModifier.h"
#include "lang/Assigner.h"
#include "lang/Context.h"
#include "lang/Element.h"
#include "lang/construct/CodeBlock.h"
#include "lang/construct/Function.h"
#include "lang/construct/FunctionGroup.h"
#include "lang/construct/Member.h"
#include "lang/construct/Variable.h"
#include "lang/type/Type.h"
#include "lang/utility/Identifier.h"
#include "lang/utility/OwningHandle.h"
#include "lang/utility/TypeRegistry.h"

class ConstantExpression;
class Storage;

namespace lang
{
    class Description;
}

namespace lang
{
    /**
     * The top level scope.
     */
    class GlobalScope
        : public Scope
        , public lang::Element<GlobalScope, ANCE_CONSTRUCTS>
    {
      public:
        explicit GlobalScope(bool is_containing_runtime);

        lang::Scope* scope() override;

        /**
         * Get the context, in which all basic systems like the typesystem are defined.
         */
        lang::Context& context() override;
        /**
         * Get the context, in which all basic systems like the typesystem are defined.
         */
        [[nodiscard]] lang::Context const& context() const override;

        lang::GlobalScope*                     getGlobalScope() override;
        [[nodiscard]] lang::GlobalScope const* getGlobalScope() const override;
        llvm::DIScope*                         getDebugScope(CompileContext& context) const override;

        void validate(ValidationLogger& validation_logger) const;

        [[nodiscard]] Owned<lang::GlobalScope> expand() const;
        void                                   determineFlow();

        void validateFlow(ValidationLogger& validation_logger) const;

        /**
         * Add an description element to this scope.
         * @param description The description to add.
         */
        void addDescription(Owned<lang::Description> description);

        /**
         * Add a function to this scope.
         * @param function The function to add.
         */
        void addFunction(lang::OwningHandle<lang::Function> function);

        /**
         * Add a variable to this scope.
         * @param variable The variable to add.
         */
        void addVariable(lang::OwningHandle<lang::Variable> variable);

        /**
         * Add a type to this scope.
         * @param type The type to add.
         */
        void addType(lang::OwningHandle<lang::Type> type);

        /**
         * Get a type defined in this scope by it's name.
         * @param string The name of the type.
         * @return The type, or nothing if no such type is defined.
         */
        Optional<lang::ResolvingHandle<lang::Type>> getType(Identifier string);

        void registerUsage(lang::ResolvingHandle<lang::Variable> variable) override;
        void registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function_group) override;
        void registerUsage(lang::ResolvingHandle<lang::Type> type) override;

        void registerDefinition(lang::ResolvingHandle<lang::Type> type) override;

        void resolve() override;
        void postResolve() override;

        /**
         * Synchronize all (public) descriptions with the given storage.
         * @param scope The scope to sync.
         * @param storage The storage to sync with.
         */
        static void synchronize(lang::GlobalScope* scope, Storage& storage);

      protected:
        bool resolveDefinition(lang::ResolvingHandle<lang::Variable> variable) override;
        bool resolveDefinition(lang::ResolvingHandle<lang::FunctionGroup> function_group) override;
        bool resolveDefinition(lang::ResolvingHandle<lang::Type> type) override;

      private:
        [[nodiscard]] Optional<lang::ResolvingHandle<lang::Function>> findEntry();

      public:
        /**
         * Check if this global scope has an entry point.
         * The default entry point is a main method returning ui32.
         * @return True if there is an entry point.
         */
        [[nodiscard]] bool hasEntry() const;

        /**
         * Get the entry point. Fails if there is no entry point.
         * @return The entry point.
         */
        lang::ResolvingHandle<lang::Function> getEntry();

        /**
         * Create the native content backing methods and functions. It is required for the actual build.
         * @param context The current compile context.
         */
        void createNativeBacking(CompileContext& context);

        /**
         * Build all functions in this scope.
         * @param context The current compile context.
         */
        void buildFunctions(CompileContext& context);

        /**
         * Build all initialization required by global entities.
         * @param context The current compile context.
         */
        void buildInitialization(CompileContext& context);
        void buildFinalization(CompileContext& context) override;

      private:
        lang::ResolvingHandle<lang::FunctionGroup> prepareDefinedFunctionGroup(Identifier name);

        std::map<lang::Identifier, std::vector<Owned<lang::Description>>> compatible_descriptions_;
        std::set<lang::Identifier>                                        conflicting_description_names_;
        std::vector<Owned<lang::Description>>                             conflicting_descriptions_;

        std::map<lang::Identifier, lang::OwningHandle<lang::FunctionGroup>> undefined_function_groups_;
        std::map<lang::Identifier, lang::OwningHandle<lang::FunctionGroup>> defined_function_groups_;

        std::map<lang::Identifier, lang::OwningHandle<lang::Variable>> global_undefined_variables_;
        std::map<lang::Identifier, lang::OwningHandle<lang::Variable>> global_defined_variables_;

        std::map<lang::Identifier, lang::OwningHandle<lang::Type>> undefined_types_;
        std::map<lang::Identifier, lang::OwningHandle<lang::Type>> defined_types_;

        std::set<lang::Identifier>    defined_names_;

        Optional<Owned<lang::Context>> context_;
    };
}

#endif
