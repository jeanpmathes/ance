#ifndef ANCE_SRC_ANCE_CONSTRUCT_FUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_FUNCTION_H_

#include "ance/scope/Scope.h"

#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/construct/FunctionDefinition.h"
#include "ance/construct/Parameter.h"
#include "ance/construct/Signature.h"

namespace ance
{
    class Value;
    class LocalScope;
    class Type;
}

class CompileContext;
class ValidationLogger;

namespace ance
{
    /**
     * A function.
     */
    class Function
        : public ance::Scope
        , public HandleTarget<ance::Function>
    {
      public:
        /**
         * Create a new function.
         * @param function_name The function name.
         */
        explicit Function(std::string function_name);

        /**
         * Get the name of this function.
         * @return The name.
         */
        [[nodiscard]] const std::string& name() const;

        /**
         * Get whether this function is defined.
         */
        [[nodiscard]] bool isDefined() const;

        /**
         * Define this function as extern.
         * @param containing_scope The function containing scope.
         * @param return_type The return type.
         * @param return_type_location The location of the return type.
         * @param parameters The parameters.
         * @param location The location of the function declaration.
         */
        void defineAsExtern(ance::Scope*                                         containing_scope,
                            ance::ResolvingHandle<ance::Type>                    return_type,
                            ance::Location                                       return_type_location,
                            const std::vector<std::shared_ptr<ance::Parameter>>& parameters,
                            ance::Location                                       location);

        /**
         * Define this function as a custom function.
         * @param access The access level.
         * @param return_type The return type of the function.
         * @param return_type_location The location of the return type.
         * @param parameters The parameters for this function.
         * @param containing_scope The scope containing the function.
         * @param declaration_location The location of the function declaration.
         * @param definition_location The location of the function definition, meaning its code.
         */
        void defineAsCustom(AccessModifier                                       access,
                            ance::ResolvingHandle<ance::Type>                    return_type,
                            ance::Location                                       return_type_location,
                            const std::vector<std::shared_ptr<ance::Parameter>>& parameters,
                            ance::Scope*                                         containing_scope,
                            ance::Location                                       declaration_location,
                            ance::Location                                       definition_location);

        /**
         * Get the return type of this function.
         * @return The return type.
         */
        [[nodiscard]] ance::ResolvingHandle<ance::Type> returnType() const;

        /**
         * Get the signature of this function.
         * @return The function signature.
         */
        [[nodiscard]] const ance::Signature& signature() const;

        /**
         * Get the type of a parameter.
         * @param index The index of the parameter. Must be smaller than the parameter count.
         * @return The type of the selected parameter.
         */
        [[nodiscard]] ance::ResolvingHandle<ance::Type> parameterType(size_t index) const;

        /**
         * Get the parameter count.
         * @return The number of parameters this function is called with.
         */
        [[nodiscard]] size_t parameterCount() const;

        /**
         * Get the source location of this function.
         * @return The source location.
         */
        [[nodiscard]] ance::Location location() const;

        /**
         * Get whether this function is mangled.
         * @return True if this function is mangled, false otherwise.
         */
        [[nodiscard]] bool isMangled() const;

        /**
         * Push a statement to the end of the statement list.
         * @param statement The statement to add.
         */
        void pushStatement(Statement* statement);

        /**
         * Add a return. Call this method in the build method of a statement.
         * @param value The value to return or nullptr if nothing is returned.
         */
        void addReturn(const std::shared_ptr<ance::Value>& value = nullptr);

        void validate(ValidationLogger& validation_logger) override;

        /**
         * Create the native content of this function, allowing building function code and calling this function.
         * @param context The current compile context.
         */
        void createNativeBacking(CompileContext* context);

        /**
         * Build the function definition. This will be called after building the name.
         * @param context The current compile context.
         */
        void build(CompileContext* context);

        /**
         * Validate a call to this function.
         * @param arguments The arguments that will be passed to the function and their source location.
         * @param location The source location of the function call.
         * @param validation_logger A logger to log validation messages.
         * @return True if the call is valid.
         */
        bool validateCall(const std::vector<std::pair<std::shared_ptr<ance::Value>, ance::Location>>& arguments,
                          ance::Location                                                              location,
                          ValidationLogger& validation_logger);

        /**
         * Build a call to this function.
         * @param arguments The arguments to pass to the function.
         * @param context The current compile context.
         * @return The return value. Will be null for return type void.
         */
        std::shared_ptr<ance::Value> buildCall(const std::vector<std::shared_ptr<ance::Value>>& arguments,
                                               CompileContext*                                  context) const;

        ance::Scope*       scope() override;
        ance::GlobalScope* getGlobalScope() override;
        llvm::DIScope*     getDebugScope(CompileContext* context) override;

        /**
         * Get the scope inside of this function, if there is any.
         * @return A scope or null.
         */
        ance::LocalScope* getInsideScope();

        void registerUsage(ance::ResolvingHandle<ance::Variable> variable) override;
        void registerUsage(ance::ResolvingHandle<ance::FunctionGroup> function_group) override;
        void registerUsage(ance::ResolvingHandle<ance::Type> type) override;

        void registerDefinition(ance::ResolvingHandle<ance::Type> type) override;

        void resolve() override;

      protected:
        bool resolveDefinition(ance::ResolvingHandle<ance::Variable> variable) override;
        bool resolveDefinition(ance::ResolvingHandle<ance::FunctionGroup> function_group) override;
        bool resolveDefinition(ance::ResolvingHandle<ance::Type> type) override;

      private:
        std::string name_;

        std::unique_ptr<ance::FunctionDefinition> definition_ {};
    };
}

#endif