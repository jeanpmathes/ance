#ifndef ANCE_SRC_ANCE_SCOPE_GLOBALSCOPE_H_
#define ANCE_SRC_ANCE_SCOPE_GLOBALSCOPE_H_

#include "Scope.h"

#include <optional>
#include <vector>

#include "ance/Assigner.h"
#include "ance/construct/Function.h"
#include "ance/construct/FunctionGroup.h"
#include "ance/construct/Variable.h"
#include "ance/type/Type.h"
#include "ance/utility/OwningHandle.h"
#include "ance/utility/TypeRegistry.h"

class ConstantExpression;

namespace ance
{
    /**
     * The top level scope.
     */
    class GlobalScope : public Scope
    {
      public:
        ance::Scope* scope() override;

        ance::GlobalScope* getGlobalScope() override;
        llvm::DIScope*     getDebugScope(CompileContext* context) override;

        void validate(ValidationLogger& validation_logger) override;

        /**
         * Define a global variable.
         * @param access The access level.
         * @param is_constant Whether the variable is a constant.
         * @param identifier The identifier of the variable.
         * @param type The type of the variable.
         * @param assigner The assigner to use for the initial assignment.
         * @param initializer The constant initializer.
         * @param location The source location.
         */
        void defineGlobalVariable(AccessModifier                    access,
                                  bool                              is_constant,
                                  const std::string&                identifier,
                                  ance::ResolvingHandle<ance::Type> type,
                                  ance::Location                    type_location,
                                  Assigner                          assigner,
                                  ConstantExpression*               initializer,
                                  ance::Location                    location);

        /**
         * Define an extern function in this scope.
         * @param identifier The name of the function.
         * @param return_type The return type.
         * @param parameters The parameters.
         * @param location The location of the function declaration.
         * @return A handle to the defined function.
         */
        ance::ResolvingHandle<ance::Function> defineExternFunction(
            const std::string&                                   identifier,
            ance::ResolvingHandle<ance::Type>                    return_type,
            ance::Location                                       return_type_location,
            const std::vector<std::shared_ptr<ance::Parameter>>& parameters,
            ance::Location                                       location);

        /**
         * Define a custom function in this scope.
         * @param identifier The name of the function.
         * @param access The access level.
         * @param return_type The return type of the function.
         * @param parameters The parameters for this function.
         * @param declaration_location The location of the function declaration.
         * @param definition_location The location of the function definition, meaning its code.
         * @return A handle to the defined function.
         */
        ance::ResolvingHandle<ance::Function> defineCustomFunction(
            const std::string&                                   identifier,
            AccessModifier                                       access,
            ance::ResolvingHandle<ance::Type>                    return_type,
            ance::Location                                       return_type_location,
            const std::vector<std::shared_ptr<ance::Parameter>>& parameters,
            ance::Location                                       declaration_location,
            ance::Location                                       definition_location);

        /**
         * Define a type that behaves like another type.
         * @param identifier The name of the new type.
         * @param original The original type.
         */
        void defineTypeAsOther(const std::string&                identifier,
                               ance::ResolvingHandle<ance::Type> original,
                               ance::Location                    definition_location,
                               ance::Location                    original_type_location);

        /**
         * Define a type that is an alias for another type.
         * @param identifier The name of the alias.
         * @param actual The other type.
         */
        void defineTypeAliasOther(const std::string&                identifier,
                                  ance::ResolvingHandle<ance::Type> actual,
                                  ance::Location                    definition_location,
                                  ance::Location                    actual_type_location);

        /**
         * Get a type defined in this scope by it's name.
         * @param string The name of the type.
         * @return The type, or nothing if no such type is defined.
         */
        std::optional<ance::ResolvingHandle<ance::Type>> getType(const std::string& string);

        /**
         * Add a type registry so it will get the chance to resolve types.
         * @param registry The registry to add. Only add a registry once.
         */
        void addTypeRegistry(ance::TypeDefinitionRegistry* registry);

        void registerUsage(ance::ResolvingHandle<ance::Variable> variable) override;
        void registerUsage(ance::ResolvingHandle<ance::FunctionGroup> function_group) override;
        void registerUsage(ance::ResolvingHandle<ance::Type> type) override;

        void registerDefinition(ance::ResolvingHandle<ance::Type> type) override;

        void resolve() override;

      protected:
        bool resolveDefinition(ance::ResolvingHandle<ance::Variable> variable) override;
        bool resolveDefinition(ance::ResolvingHandle<ance::FunctionGroup> function_group) override;
        bool resolveDefinition(ance::ResolvingHandle<ance::Type> type) override;

      public:
        /**
         * Check if this global scope has an entry point.
         * The default entry point is a main method returning ui32.
         * @return True if there is an entry point.
         */
        bool hasEntry();

        /**
         * Check if this global scope has an exit point
         * The default exit point is an exit method taking a ui32.
         * @return True if there is an exit point.
         */
        bool hasExit();

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

      private:
        ance::ResolvingHandle<ance::FunctionGroup> prepareDefinedFunctionGroup(const std::string& name);
        ance::OwningHandle<ance::Type>             retrieveUndefinedType(const std::string& identifier);

        std::vector<std::pair<std::string, ance::Location>> errors_;

        std::vector<ance::TypeDefinitionRegistry*> type_registries_;

        std::map<std::string, ance::OwningHandle<ance::Variable>> global_undefined_variables_;
        std::map<std::string, ance::OwningHandle<ance::Variable>> global_defined_variables_;

        std::map<std::string, ance::OwningHandle<ance::FunctionGroup>> undefined_function_groups_;
        std::map<std::string, ance::OwningHandle<ance::FunctionGroup>> defined_function_groups_;

        std::map<std::string, ance::OwningHandle<ance::Type>> undefined_types_;
        std::map<std::string, ance::OwningHandle<ance::Type>> defined_types_;
    };
}
#endif
