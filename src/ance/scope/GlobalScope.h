#ifndef ANCE_SRC_ANCE_SCOPE_GLOBALSCOPE_H_
#define ANCE_SRC_ANCE_SCOPE_GLOBALSCOPE_H_

#include "Scope.h"

#include <vector>

#include "ance/Assigner.h"
#include "ance/construct/Function.h"
#include "ance/construct/Variable.h"
#include "ance/utility/OwningHandle.h"

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

        bool        isTypeRegistered(const std::string& type_name) override;
        ance::Type* getType(const std::string& type_name) override;
        void        registerType(ance::Type* type) override;

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
        void defineGlobalVariable(AccessModifier      access,
                                  bool                is_constant,
                                  const std::string&  identifier,
                                  ance::Type*         type,
                                  Assigner            assigner,
                                  ConstantExpression* initializer,
                                  ance::Location      location);

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
            ance::Type*                                          return_type,
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
            ance::Type*                                          return_type,
            const std::vector<std::shared_ptr<ance::Parameter>>& parameters,
            ance::Location                                       declaration_location,
            ance::Location                                       definition_location);

        void registerUsage(ance::ResolvingHandle<ance::Variable> variable) override;
        void registerUsage(ance::ResolvingHandle<ance::Function> function) override;

        void resolve() override;

      protected:
        bool resolveDefinition(ance::ResolvingHandle<ance::Variable> variable) override;
        bool resolveDefinition(ance::ResolvingHandle<ance::Function> function) override;

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
        ance::OwningHandle<ance::Function> retrieveUndefinedFunction(std::string identifier);

        std::vector<std::pair<std::string, ance::Location>> errors_;

        std::map<std::string, ance::Type*> types_;

        std::map<std::string, ance::OwningHandle<ance::Variable>> global_undefined_variables_;
        std::map<std::string, ance::OwningHandle<ance::Variable>> global_defined_variables_;

        std::map<std::string, ance::OwningHandle<ance::Function>> undefined_functions_;
        std::map<std::string, ance::OwningHandle<ance::Function>> defined_functions_;
    };
}
#endif
