#ifndef ANCE_SRC_LANG_SCOPE_GLOBALSCOPE_H_
#define ANCE_SRC_LANG_SCOPE_GLOBALSCOPE_H_

#include "Scope.h"

#include <optional>
#include <vector>

#include "lang/AccessModifier.h"
#include "lang/Assigner.h"
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

      private:
        bool is_containing_runtime_ {false};

      public:
        /**
         * Check whether this scope contains the runtime.
         * @return True if the runtime is contained.
         */
        [[nodiscard]] bool isContainingRuntime() const;

      public:
        lang::Scope* scope() override;

        lang::GlobalScope*       getGlobalScope() override;
        lang::GlobalScope const* getGlobalScope() const override;
        llvm::DIScope*           getDebugScope(CompileContext& context) const override;

        void validate(ValidationLogger& validation_logger) const;

        void expand();
        void determineFlow();

        void validateFlow(ValidationLogger& validation_logger) const;

        /**
         * Use this for elements that depend on the runtime.
         * @param location The location of the element.
         * @param validation_logger The logger to use for validation.
         * @return True if the runtime is available.
         */
        bool validateRuntimeDependency(lang::Location location, ValidationLogger& validation_logger) const;

        /**
         * Define a type that is an alias for another type.
         * @param name The name of the alias.
         * @param actual The other type.
         */
        void defineTypeAliasOther(Identifier                        name,
                                  lang::ResolvingHandle<lang::Type> actual,
                                  lang::Location                    definition_location,
                                  lang::Location                    actual_type_location);

        /**
         * Define a struct.
         * @param access The access level.
         * @param name The name of the struct.
         * @param members The members of the struct.
         * @param definition_location The location of the struct definition.
         */
        void defineStruct(lang::AccessModifier             access,
                          Identifier                       name,
                          std::vector<Owned<lang::Member>> members,
                          lang::Location                   definition_location);

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
         * Get a type defined in this scope by it's name.
         * @param string The name of the type.
         * @return The type, or nothing if no such type is defined.
         */
        Optional<lang::ResolvingHandle<lang::Type>> getType(Identifier string);

        /**
         * Add a type registry so it will get the chance to resolve types.
         * @param registry The registry to add. Only add a registry once.
         */
        void addTypeRegistry(lang::TypeDefinitionRegistry* registry);

        void registerUsage(lang::ResolvingHandle<lang::Variable> variable) override;
        void registerUsage(lang::ResolvingHandle<lang::FunctionGroup> function_group) override;
        void registerUsage(lang::ResolvingHandle<lang::Type> type) override;

        void registerDefinition(lang::ResolvingHandle<lang::Type> type) override;

        void resolve() override;
        void postResolve() override;

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

        /**
         * Get all functions that should be exported.
         * @return The exported functions.
         */
        std::vector<std::string> getExportFunctions() const;

      private:
        lang::ResolvingHandle<lang::FunctionGroup> prepareDefinedFunctionGroup(Identifier name);
        lang::OwningHandle<lang::Type>             retrieveUndefinedType(Identifier name);

        std::map<lang::Identifier, std::vector<Owned<lang::Description>>> compatible_descriptions_;
        std::set<lang::Identifier>                                        conflicting_description_names_;
        std::vector<Owned<lang::Description>>                             conflicting_descriptions_;

        std::vector<lang::TypeDefinitionRegistry*> type_registries_;

        std::map<lang::Identifier, lang::OwningHandle<lang::FunctionGroup>> undefined_function_groups_;
        std::map<lang::Identifier, lang::OwningHandle<lang::FunctionGroup>> defined_function_groups_;
        std::vector<lang::OwningHandle<lang::Function>>                     invalid_functions_;

        std::map<lang::Identifier, lang::OwningHandle<lang::Variable>> global_undefined_variables_;
        std::map<lang::Identifier, lang::OwningHandle<lang::Variable>> global_defined_variables_;
        std::vector<lang::OwningHandle<lang::Variable>>                invalid_variables_;

        std::map<lang::Identifier, lang::OwningHandle<lang::Type>> undefined_types_;
        std::map<lang::Identifier, lang::OwningHandle<lang::Type>> defined_types_;

        std::set<lang::Identifier>    defined_names_;
        std::vector<lang::Identifier> duplicated_names_;

        bool expanded_ = false;
    };
}
#endif
