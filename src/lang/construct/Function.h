#ifndef ANCE_SRC_LANG_CONSTRUCT_FUNCTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_FUNCTION_H_

#include "lang/scope/Scope.h"

#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/AccessModifier.h"
#include "lang/Element.h"
#include "lang/construct/BasicBlock.h"
#include "lang/construct/CodeBlock.h"
#include "lang/construct/FunctionDefinition.h"
#include "lang/construct/Parameter.h"
#include "lang/construct/Signature.h"
#include "lang/utility/OwningHandle.h"

namespace lang
{
    class Value;
    class LocalScope;
    class Type;
    class CodeBlock;
    class PredefinedFunction;
    class InitializerFunction;
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
        explicit Function(Identifier function_name);

        /**
         * Get the name of this function.
         * @return The name.
         */
        [[nodiscard]] Identifier const& name() const;

        /**
         * Get whether this function is defined.
         */
        [[nodiscard]] bool isDefined() const;

        /**
         * Define this function as imported.
         * @param containing_scope The function containing scope.
         * @param access The access level.
         * @param return_type The return type.
         * @param return_type_location The location of the return type.
         * @param parameters The parameters.
         * @param location The location of the function declaration.
         */
        void defineAsImported(Scope&                                      containing_scope,
                              lang::AccessModifier                        access,
                              lang::ResolvingHandle<lang::Type>           return_type,
                              lang::Location                              return_type_location,
                              std::vector<Shared<lang::Parameter>> const& parameters,
                              lang::Location                              location);

        /**
         * Define this function as a custom function.
         * @param access The access level.
         * @param return_type The return type of the function.
         * @param return_type_location The location of the return type.
         * @param parameters The parameters for this function.
         * @param block The code block for this function.
         * @param containing_scope The scope containing the function.
         * @param declaration_location The location of the function declaration.
         * @param definition_location The location of the function definition, meaning its code.
         */
        void defineAsCustom(lang::AccessModifier                        access,
                            lang::ResolvingHandle<lang::Type>           return_type,
                            lang::Location                              return_type_location,
                            std::vector<Shared<lang::Parameter>> const& parameters,
                            Statement&                                  block,
                            Scope&                                      containing_scope,
                            lang::Location                              declaration_location,
                            lang::Location                              definition_location);

        /**
         * Define this function as a predefined function.
         * @param return_type The return type of the function.
         * @param parameters The parameters for this function.
         * @param containing_scope The scope containing the function.
         * @param location The location of the function.
         * @return The predefined function.
         */
        PredefinedFunction& defineAsPredefined(lang::ResolvingHandle<lang::Type>           return_type,
                                               std::vector<Shared<lang::Parameter>> const& parameters,
                                               Scope&                                      containing_scope,
                                               lang::Location                              location);

        /**
         * Define this function as a variable initialization function.
         * @param code The initializer.
         * @param containing_scope The scope containing the function.
         */
        InitializerFunction& defineAsInit(Statement& code, Scope& containing_scope);

        /**
         * Define a local variable that is a parameter.
         * @param name The name.
         * @param type The type.
         * @param type_location The source location of the type.
         * @param value The initial value.
         * @param parameter_no The number of the parameter. Counting starts with one.
         * @param location The source location.
         * @return The defined variable or nothing if defining is not possible.
         */
        Optional<lang::ResolvingHandle<lang::Variable>> defineParameterVariable(Identifier const&                 name,
                                                                                lang::ResolvingHandle<lang::Type> type,
                                                                                lang::Location      type_location,
                                                                                Shared<lang::Value> value,
                                                                                unsigned            parameter_no,
                                                                                lang::Location      location);

        /**
         * Get the access level of this function.
         * @return The access level.
         */
        [[nodiscard]] lang::AccessModifier access() const;

        /**
         * Get the return type of this function.
         * @return The return type.
         */
        lang::ResolvingHandle<lang::Type> returnType();

        /**
         * Get the return type of this function.
         * @return The return type.
         */
        [[nodiscard]] lang::Type const& returnType() const;

        /**
         * Get the signature of this function.
         * @return The function signature.
         */
        [[nodiscard]] lang::Signature const& signature() const;

        /**
         * Get the code block of this function, if there is one.
         * @return The code block.
         */
        [[nodiscard]] Statement const* code() const;

        /**
         * Get the type of a parameter.
         * @param index The index of the parameter. Must be smaller than the parameter count.
         * @return The type of the selected parameter.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Type> parameterType(size_t index);

        /**
         * Get the type of a parameter.
         * @param index The index of the parameter. Must be smaller than the parameter count.
         * @return The type of the selected parameter.
         */
        [[nodiscard]] lang::Type const& parameterType(size_t index) const;

        /**
         * Get the name of a parameter.
         * @param index The index of the parameter. Must be smaller than the parameter count.
         * @return The name of the selected parameter.
         */
        [[nodiscard]] lang::Identifier const& parameterName(size_t index) const;

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
         * Whether this function is imported, meaning the definition is not part of this module.
         * @return True if this function is imported, false otherwise.
         */
        [[nodiscard]] bool isImported() const;

        /**
         * Determine the control flow in this function and build the CFG.
         * This step is necessary to build.
         */
        void determineFlow();

        /**
         * Validate the flow of this function.
         * @param validation_logger The validation logger.
         */
        void validateFlow(ValidationLogger& validation_logger) const;

        /**
         * Create the native content of this function, allowing building function code and calling this function.
         * @param context The current compile context.
         */
        void createNativeBacking(CompileContext& context);

        /**
         * Build the function definition. This will be called after building the name.
         * @param context The current compile context.
         */
        void build(CompileContext& context);

        /**
         * Build all parameter declarations.
         * @param context The current compile context.
         */
        void buildDeclarations(CompileContext& context);

        void buildFinalization(CompileContext& context) override;

        /**
         * Validate a call to this function.
         * @param arguments The arguments that will be passed to the function and their source location.
         * @param location The source location of the function call.
         * @param validation_logger A logger to log validation messages.
         * @return True if the call is valid.
         */
        bool validateCall(
            std::vector<std::pair<std::reference_wrapper<lang::Value const>, lang::Location>> const& arguments,
            lang::Location                                                                           location,
            ValidationLogger& validation_logger) const;

        /**
         * Build a call to this function.
         * @param arguments The arguments to pass to the function.
         * @param context The current compile context.
         * @return The return value. Will be null for return type void.
         */
        Optional<Shared<lang::Value>> buildCall(std::vector<Shared<lang::Value>> const& arguments,
                                                CompileContext&                         context);

        lang::Scope*                           scope() override;
        lang::GlobalScope*                     getGlobalScope() override;
        [[nodiscard]] lang::GlobalScope const* getGlobalScope() const override;
        llvm::DIScope*                         getDebugScope(CompileContext& context) const override;

        /**
         * Get the scope inside of this function, if there is any.
         * @return A scope or null.
         */
        lang::LocalScope* getInsideScope();

        /**
         * Get the basic blocks for this function.
         * @return A vector containing all basic blocks.
         */
        [[nodiscard]] std::vector<lang::BasicBlock*> const& getBasicBlocks() const;

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
        lang::Identifier name_;

        Optional<Owned<lang::FunctionDefinition>> definition_ {};

        std::map<lang::Identifier, lang::OwningHandle<lang::Variable>> undefined_variables_ {};
        std::map<lang::Identifier, lang::OwningHandle<lang::Variable>> defined_parameters_ {};

        std::map<lang::Identifier, lang::OwningHandle<lang::FunctionGroup>> undefined_function_groups_ {};

        std::map<lang::Identifier, lang::OwningHandle<lang::Type>> undefined_types_ {};
    };
}

#endif
