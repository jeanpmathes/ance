#ifndef ANCE_SRC_LANG_CONSTRUCT_FUNCTION_H_
#define ANCE_SRC_LANG_CONSTRUCT_FUNCTION_H_

#include "lang/scope/OrderedScope.h"

#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "lang/AccessModifier.h"
#include "lang/Element.h"
#include "lang/construct/BasicBlock.h"
#include "lang/construct/Parameter.h"
#include "lang/utility/OwningHandle.h"

namespace lang
{
    class Value;
    class LocalScope;
    class Type;
    class CodeBlock;
    class PredefinedFunction;
    class InitializerFunction;
    class FunctionDefinition;
    class Signature;
}

class Execution;
class ValidationLogger;

namespace lang
{
    /**
     * A function.
     */
    class Function
        : public lang::OrderedScope
        , public HandleTarget<lang::Function>
        , public lang::Element<Function, ANCE_CONSTRUCTS>
        , public Entity
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
        [[nodiscard]] Identifier const& name() const override;

        /**
         * Get the linkage name of this function.
         * @return The linkage name.
         */
        [[nodiscard]] std::string getLinkageName() const;

        /**
         * Get whether this function is defined.
         */
        [[nodiscard]] bool isDefined() const override;

        /**
         * Get whether this function is part of the runtime library.
         * @return True if this function is part of the runtime library, false otherwise.
         */
        [[nodiscard]] bool isRuntime() const;

        /**
         * Get whether this function can be evaluated at compile time.
         * This does not mean that it cannot be called at runtime.
         * @return True if this function can be evaluated at compile time, false otherwise.
         */
        [[nodiscard]] bool isCMP() const;

        /**
         * Whether to preserve the unit return type or use void.
         * Has no effect if the return type is not unit.
         * @return True if the unit return type should be preserved, false if it should be replaced with void.
         */
        [[nodiscard]] bool preserveUnitReturn() const;

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
         * @param is_cmp Whether the function can be evaluated at compile time.
         * @param return_type The return type of the function.
         * @param return_type_location The location of the return type.
         * @param parameters The parameters for this function.
         * @param block The code block for this function.
         * @param containing_scope The scope containing the function.
         * @param declaration_location The location of the function declaration.
         * @param definition_location The location of the function definition, meaning its code.
         */
        void defineAsCustom(lang::AccessModifier                        access,
                            bool                                        is_cmp,
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
         * @param is_constructor Whether the function is a constructor.
         * @param parameters The parameters for this function.
         * @param access_modifier The access level of the function.
         * @param is_imported Whether this function is imported.
         * @param containing_scope The scope containing the function.
         * @param location The location of the function.
         * @return The predefined function.
         */
        PredefinedFunction& defineAsPredefined(lang::ResolvingHandle<lang::Type>           return_type,
                                               bool                                        is_constructor,
                                               std::vector<Shared<lang::Parameter>> const& parameters,
                                               lang::AccessModifier                        access_modifier,
                                               bool                                        is_imported,
                                               lang::Scope&                                containing_scope,
                                               lang::Location                              location);

        /**
         * Define this function as a variable initialization function.
         * @param code The initializer.
         * @param type The return type of the function.
         * @param containing_scope The scope containing the function.
         */
        InitializerFunction& defineAsInit(Statement&                        code,
                                          lang::ResolvingHandle<lang::Type> type,
                                          Scope&                            containing_scope);

        /**
         * Define this function as a runtime function, meaning it is part of the runtime library.
         * @param return_type The return type of the function.
         * @param parameters The parameters for this function.
         * @param exec The execution context.
         */
        void defineAsRuntime(lang::ResolvingHandle<lang::Type>    return_type,
                             std::vector<Shared<lang::Parameter>> parameters,
                             Execution&                           exec);

        /**
         * Define this function with a given definition.
         * @param definition The definition.
         */
        void define(Owned<lang::FunctionDefinition> definition);

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
         * Get a parameter by index.
         * @param index The index of the parameter.
         * @return The parameter.
         */
        Shared<lang::Parameter> parameter(size_t index);

        /**
         * Get a parameter by index.
         * @param index The index of the parameter.
         * @return The parameter.
         */
        [[nodiscard]] lang::Parameter const& parameter(size_t index) const;

        /**
         * Get the parameter count.
         * @return The number of parameters this function is called with.
         */
        [[nodiscard]] size_t parameterCount() const;

        /**
         * Get the parameters of this function.
         * @return The parameters.
         */
        [[nodiscard]] std::vector<Shared<lang::Parameter>> const& parameters() const;

        /**
         * Get the source location of this function.
         * @return The source location.
         */
        [[nodiscard]] lang::Location location() const;

        [[nodiscard]] Optional<lang::Location> getDefinitionLocation() const;

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
         * Create the declaration of this function, allowing building function code and calling this function.
         * @param exec The current execution context.
         */
        void registerDeclaration(Execution& exec) const;

        /**
         * Validate a call to this function.
         * @param arguments The arguments that will be passed to the function.
         * @param location The source location of the function call.
         * @param validation_logger A logger to log validation messages.
         * @return True if the call is valid.
         */
        bool validateCall(std::vector<std::reference_wrapper<Expression const>> const& arguments,
                          lang::Location                                               location,
                          ValidationLogger&                                            validation_logger) const;

        /**
         * Build a call to this function.
         * @param arguments The arguments to pass to the function.
         * @param exec The current execution context.
         * @return The return value.
         */
        Shared<lang::Value> execCall(std::vector<Shared<lang::Value>> const& arguments, Execution& exec) const;

        lang::Scope&                     scope() override;
        [[nodiscard]] lang::Scope const& scope() const override;

        [[nodiscard]] bool isPartOfFunction() const override;

        /**
         * Get the entry basic block of this function, or null if there is none.
         * @return The entry basic block.
         */
        [[nodiscard]] lang::BasicBlock const* getEntryBlock() const;

        /**
         * Get the basic blocks for this function.
         * @return A vector containing all basic blocks, even if they are not reachable.
         */
        [[nodiscard]] std::vector<lang::BasicBlock*> const& getBasicBlocks() const;

        void resolveFollowingOrder() override;
        void postResolve() override;

        void registerEntityDeclarationsFollowingOrder(Execution& exec) const override;

        ResolvingHandle<lang::Entity> getUndefinedClone(Context& new_context) const override;

      private:
        lang::Identifier                          name_;
        Optional<Owned<lang::FunctionDefinition>> definition_ {};
    };
}

#endif
