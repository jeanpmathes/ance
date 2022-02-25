#ifndef ANCE_SRC_LANG_CONSTRUCT_FUNCTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_FUNCTION_H_

#include "lang/scope/Scope.h"

#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/construct/FunctionDefinition.h"
#include "lang/construct/Parameter.h"
#include "lang/construct/Signature.h"
#include "lang/AccessModifier.h"
#include "lang/Element.h"
#include "lang/construct/BasicBlock.h"

namespace lang
{
    class Value;
    class LocalScope;
    class Type;
}

class CompileContext;
class ValidationLogger;

namespace lang
{
    /**
     * A function.
     */
    class Function
        : public lang::Scope
        , public HandleTarget<lang::Function>
        , public lang::Element<Function, ANCE_CONSTRUCTS>
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
        void defineAsExtern(lang::Scope*                                         containing_scope,
                            lang::ResolvingHandle<lang::Type>                    return_type,
                            lang::Location                                       return_type_location,
                            const std::vector<std::shared_ptr<lang::Parameter>>& parameters,
                            lang::Location                                       location);

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
        void defineAsCustom(lang::AccessModifier                                 access,
                            lang::ResolvingHandle<lang::Type>                    return_type,
                            lang::Location                                       return_type_location,
                            const std::vector<std::shared_ptr<lang::Parameter>>& parameters,
                            lang::Scope*                                         containing_scope,
                            lang::Location                                       declaration_location,
                            lang::Location                                       definition_location);

        /**
         * Get the return type of this function.
         * @return The return type.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Type> returnType() const;

        /**
         * Get the signature of this function.
         * @return The function signature.
         */
        [[nodiscard]] const lang::Signature& signature() const;

        /**
         * Get the type of a parameter.
         * @param index The index of the parameter. Must be smaller than the parameter count.
         * @return The type of the selected parameter.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Type> parameterType(size_t index) const;

        /**
         * Get the parameter count.
         * @return The number of parameters this function is called with.
         */
        [[nodiscard]] size_t parameterCount() const;

        /**
         * Get the source location of this function.
         * @return The source location.
         */
        [[nodiscard]] lang::Location location() const;

        /**
         * Get whether this function is mangled.
         * @return True if this function is mangled, false otherwise.
         */
        [[nodiscard]] bool isMangled() const;

        /**
         * Add a statement to this function. This is only valid before finalization.
         * @param statement The function to add.
         */
        void pushStatement(std::unique_ptr<Statement> statement);

        /**
         * Finalize the function definition. No blocks may be added after this.
         */
        void finalizeDefinition();

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
        bool validateCall(const std::vector<std::pair<std::shared_ptr<lang::Value>, lang::Location>>& arguments,
                          lang::Location                                                              location,
                          ValidationLogger& validation_logger);

        /**
         * Build a call to this function.
         * @param arguments The arguments to pass to the function.
         * @param context The current compile context.
         * @return The return value. Will be null for return type void.
         */
        std::shared_ptr<lang::Value> buildCall(const std::vector<std::shared_ptr<lang::Value>>& arguments,
                                               CompileContext*                                  context) const;

        lang::Scope*       scope() override;
        lang::GlobalScope* getGlobalScope() override;
        llvm::DIScope*     getDebugScope(CompileContext* context) override;

        /**
         * Get the scope inside of this function, if there is any.
         * @return A scope or null.
         */
        lang::LocalScope* getInsideScope();

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
        std::string name_;

        std::unique_ptr<lang::FunctionDefinition> definition_ {};
    };
}

#endif