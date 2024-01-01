#ifndef ANCE_SRC_LANG_CONSTRUCT_FUNCTIONDEFINITION_H_
#define ANCE_SRC_LANG_CONSTRUCT_FUNCTIONDEFINITION_H_

#include <vector>

#include "compiler/Execution.h"
#include "lang/Element.h"
#include "lang/construct/BasicBlock.h"
#include "lang/construct/Parameter.h"
#include "lang/construct/Signature.h"
#include "lang/utility/Identifier.h"
#include "lang/utility/Location.h"

namespace lang
{
    class Variable;
    class Scope;
    class GlobalScope;
    class LocalScope;
    class Function;
}

class Statement;
class ValidationLogger;

namespace lang
{
    class FunctionDefinition
    {
      public:
        explicit FunctionDefinition(lang::Function&                      function,
                                    lang::Scope&                         containing_scope,
                                    lang::ResolvingHandle<lang::Type>    type,
                                    lang::Location                       return_type_location,
                                    std::vector<Shared<lang::Parameter>> parameters,
                                    lang::Location                       location);

        virtual void setup();

        /**
         * Get the name of this function.
         * @return The name.
         */
        [[nodiscard]] Identifier const& name() const;

        /**
         * Get the containing scope.
         */
        [[nodiscard]] lang::Scope& scope() const;

        /**
         * Get the function.
         */
        [[nodiscard]] lang::Function& function() const;

        /**
         * Get the access level.
         */
        [[nodiscard]] virtual lang::AccessModifier access() const;

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
         * Get the function signature.
         * @return The function signature.
         */
        [[nodiscard]] lang::Signature const& signature() const;

        /**
         * Get the code of this function, if any.
         * @return The code.
         */
        [[nodiscard]] virtual Statement const* code() const;

        /**
         * Get the location of the return type.
         * @return The location.
         */
        [[nodiscard]] lang::Location returnTypeLocation() const;

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
         * Get whether the name of this function is mangled.
         * @return True if the name is mangled.
         */
        [[nodiscard]] virtual bool isMangled() const = 0;

        /**
         * Get whether this function is imported.
         * @return True if the function is imported.
         */
        [[nodiscard]] virtual bool isImported() const;

        virtual void resolveFollowingOrder();

        /**
         * Called after the resolve step.
         */
        virtual void postResolve();

        /**
         * Determine and create structures to represent control flow.
         */
        virtual void determineFlow() = 0;

        /**
         * Validate the control flow of this function.
         * @param validation_logger The logger to log validation messages.
         * @return True if the control flow is valid.
         */
        virtual bool validateFlow(ValidationLogger& validation_logger) const = 0;

        /**
         * Create the native content of this function, allowing building function code and calling this function.
         * @param context The current compile context.
         */
        void createNativeBacking(CompileContext& context);

        /**
         * Build the function definition. This will be called after building the name.
         * @param context The current compile context.
         */
        virtual void build(CompileContext& context) = 0;

        /**
         * Validate a call to this function.
         * @param arguments The arguments that will be passed to the function and their source location.
         * @param location The source location of the function call.
         * @param validation_logger A logger to log validation messages.
         * @return True if the call is valid.
         */
        virtual bool validateCall(
            std::vector<std::pair<std::reference_wrapper<lang::Value const>, lang::Location>> const& arguments,
            lang::Location                                                                           location,
            ValidationLogger& validation_logger) const;

        /**
         *This method is called in FunctionDefinition::validateCall.
         */
        virtual bool doCallValidation(
            std::vector<std::pair<std::reference_wrapper<lang::Value const>, lang::Location>> const& arguments,
            lang::Location                                                                           location,
            ValidationLogger& validation_logger) const;

        /**
         * Build a call to this function.
         * @param arguments The arguments to pass to the function.
         * @param context The current compile context.
         * @return The return value.
         */
        Shared<lang::Value> buildCall(std::vector<Shared<lang::Value>> arguments, CompileContext& context);

      protected:
        /**
         * Get the function parameters.
         * @return A vector containing the parameters.
         */
        [[nodiscard]] std::vector<Shared<lang::Parameter>> const& parameters() const;

        /**
         * Get the function parameters.
         * @return A vector containing the parameters.
         */
        [[nodiscard]] std::vector<Shared<lang::Parameter>> parameters();

        /**
         * A helper to create a backing function.
         * @param access The access level of the function.
         * @param is_imported Whether this function is imported.
         * @param definition_location The location of the function definition.
         * @param is_constructor Whether this function is a constructor.
         * @param context The current compile context.
         * @return The created function.
         */
        Execution::Function createBackingFunction(lang::AccessModifier     access,
                                                  bool                     is_imported,
                                                  Optional<lang::Location> definition_location,
                                                  bool                     is_constructor,
                                                  CompileContext&          context);

        [[nodiscard]] virtual Optional<lang::Location> getDefinitionLocation() const = 0;
        [[nodiscard]] virtual bool                     isConstructor() const         = 0;

      public:
        virtual void buildDeclarationsFollowingOrder(CompileContext& context);

        Execution::Scoped getDebugScope() const;

        [[nodiscard]] virtual std::vector<lang::BasicBlock*> const& getBasicBlocks() const = 0;

        virtual ~FunctionDefinition() = default;

      private:
        lang::Function& function_;
        lang::Scope&    containing_scope_;

        lang::ResolvingHandle<lang::Type>             return_type_;
        lang::Location                                return_type_location_;
        std::vector<Shared<lang::Parameter>>          parameters_;
        lang::Location                                location_;

      protected:
        lang::Signature signature_;
        Optional<Execution::Function> function_handle_ = {};
    };
}

#endif
