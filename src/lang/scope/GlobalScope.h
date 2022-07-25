#ifndef ANCE_SRC_LANG_SCOPE_GLOBALSCOPE_H_
#define ANCE_SRC_LANG_SCOPE_GLOBALSCOPE_H_

#include "Scope.h"

#include <optional>
#include <vector>

#include "lang/Assigner.h"
#include "lang/construct/Function.h"
#include "lang/construct/FunctionGroup.h"
#include "lang/construct/Variable.h"
#include "lang/type/Type.h"
#include "lang/utility/OwningHandle.h"
#include "lang/utility/TypeRegistry.h"
#include "lang/AccessModifier.h"
#include "lang/Assigner.h"
#include "lang/Element.h"
#include "lang/utility/Identifier.h"
#include "lang/construct/CodeBlock.h"
#include "lang/construct/Member.h"

class ConstantExpression;

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
        lang::Scope* scope() override;

        lang::GlobalScope* getGlobalScope() override;
        llvm::DIScope*     getDebugScope(CompileContext* context) override;

        void validate(ValidationLogger& validation_logger) const override;

        void expand();
        void determineFlow();

        void validateFlow(ValidationLogger& validation_logger) const;

        /**
         * Define a global variable.
         * @param access The access level.
         * @param is_constant Whether the variable is a constant.
         * @param name The name of the variable.
         * @param type The type of the variable.
         * @param assigner The assigner to use for the initial assignment.
         * @param initializer The constant initializer.
         * @param location The source location.
         */
        void defineGlobalVariable(lang::AccessModifier                access,
                                  bool                                is_constant,
                                  lang::Identifier                    name,
                                  lang::ResolvingHandle<lang::Type>   type,
                                  lang::Location                      type_location,
                                  lang::Assigner                      assigner,
                                  std::unique_ptr<ConstantExpression> initializer,
                                  lang::Location                      location);

        /**
         * Define an extern function in this scope.
         * @param name The name of the function.
         * @param return_type The return type.
         * @param parameters The parameters.
         * @param location The location of the function declaration.
         */
        void defineExternFunction(Identifier                                           name,
                                  lang::ResolvingHandle<lang::Type>                    return_type,
                                  lang::Location                                       return_type_location,
                                  const std::vector<std::shared_ptr<lang::Parameter>>& parameters,
                                  lang::Location                                       location);

        /**
         * Define a custom function in this scope.
         * @param name The name of the function.
         * @param access The access level.
         * @param return_type The return type of the function.
         * @param parameters The parameters for this function.
         * @param code The code of the function.
         * @param declaration_location The location of the function declaration.
         * @param definition_location The location of the function definition, meaning its code.
         */
        void defineCustomFunction(Identifier                                           name,
                                  lang::AccessModifier                                 access,
                                  lang::ResolvingHandle<lang::Type>                    return_type,
                                  lang::Location                                       return_type_location,
                                  const std::vector<std::shared_ptr<lang::Parameter>>& parameters,
                                  std::unique_ptr<lang::CodeBlock>                     code,
                                  lang::Location                                       declaration_location,
                                  lang::Location                                       definition_location);

        /**
         * Define a type that behaves like another type.
         * @param name The name of the new type.
         * @param original The original type.
         */
        void defineTypeAsOther(Identifier                        name,
                               lang::ResolvingHandle<lang::Type> original,
                               lang::Location                    definition_location,
                               lang::Location                    original_type_location);

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
        void defineStruct(lang::AccessModifier                       access,
                          Identifier                                 name,
                          std::vector<std::unique_ptr<lang::Member>> members,
                          lang::Location                             definition_location);

        /**
         * Get a type defined in this scope by it's name.
         * @param string The name of the type.
         * @return The type, or nothing if no such type is defined.
         */
        std::optional<lang::ResolvingHandle<lang::Type>> getType(Identifier string);

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

      protected:
        bool resolveDefinition(lang::ResolvingHandle<lang::Variable> variable) override;
        bool resolveDefinition(lang::ResolvingHandle<lang::FunctionGroup> function_group) override;
        bool resolveDefinition(lang::ResolvingHandle<lang::Type> type) override;

      private:
        std::optional<lang::ResolvingHandle<lang::Function>> findEntry() const;
        std::optional<lang::ResolvingHandle<lang::Function>> findExit() const;

      public:
        /**
         * Check if this global scope has an entry point.
         * The default entry point is a main method returning ui32.
         * @return True if there is an entry point.
         */
        bool hasEntry() const;

        /**
         * Check if this global scope has an exit point
         * The default exit point is an exit method taking a ui32.
         * @return True if there is an exit point.
         */
        bool hasExit() const;

        /**
         * Get the entry point. Fails if there is no entry point.
         * @return The entry point.
         */
        lang::ResolvingHandle<lang::Function> getEntry();

        /**
         * Get the exit point. Fails if there is no exit point.
         * @return The exit point.
         */
        lang::ResolvingHandle<lang::Function> getExit();

        /**
         * Create the native content backing methods and functions. It is required for the actual build.
         * @param context The current compile context.
         */
        void createNativeBacking(CompileContext* context);

        /**
         * Build all functions in this scope.
         * @param context The current compile context.
         */
        void buildFunctions(CompileContext* context);

        void buildFinalization(CompileContext* context) override;

      private:
        lang::ResolvingHandle<lang::FunctionGroup> prepareDefinedFunctionGroup(Identifier name);
        lang::OwningHandle<lang::Type>             retrieveUndefinedType(Identifier name);

        std::vector<lang::TypeDefinitionRegistry*> type_registries_;

        std::map<lang::Identifier, lang::OwningHandle<lang::Variable>> global_undefined_variables_;
        std::map<lang::Identifier, lang::OwningHandle<lang::Variable>> global_defined_variables_;

        std::map<lang::Identifier, lang::OwningHandle<lang::FunctionGroup>> undefined_function_groups_;
        std::map<lang::Identifier, lang::OwningHandle<lang::FunctionGroup>> defined_function_groups_;

        std::map<lang::Identifier, lang::OwningHandle<lang::Type>> undefined_types_;
        std::map<lang::Identifier, lang::OwningHandle<lang::Type>> defined_types_;

        std::set<lang::Identifier>                                defined_names_;
        std::vector<std::tuple<lang::Identifier, lang::Location>> duplicated_names_;
    };
}
#endif
