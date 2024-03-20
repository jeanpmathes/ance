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
        lang::Scope& scope();

        /**
         * Get the containing scope.
         */
        [[nodiscard]] lang::Scope const& scope() const;

        /**
         * Get the function.
         */
        [[nodiscard]] lang::Function& function();

        /**
         * Get the function.
         */
        [[nodiscard]] lang::Function const& function() const;

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
        lang::Parameter const& parameter(size_t index) const;

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
         * Get whether this function is part of the runtime.
         * @return True if the function is part of the runtime.
         */
        [[nodiscard]] virtual bool isRuntime() const;

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

        void buildDeclaration(CompileContext& context) const;

        /**
         * Validate a call to this function.
         * @param arguments The arguments that will be passed to the function.
         * @param location The source location of the function call.
         * @param validation_logger A logger to log validation messages.
         * @return True if the call is valid.
         */
        virtual bool validateCall(std::vector<std::reference_wrapper<Expression const>> const& arguments,
                                  lang::Location                                               location,
                                  ValidationLogger&                                            validation_logger) const;

        /**
         *This method is called in FunctionDefinition::validateCall.
         */
        virtual bool doCallValidation(std::vector<std::reference_wrapper<Expression const>> const& arguments,
                                      lang::Location                                               location,
                                      ValidationLogger& validation_logger) const;

        /**
         * Build a call to this function.
         * @param arguments The arguments to pass to the function.
         * @param context The current compile context.
         * @return The return value.
         */
        Shared<lang::Value> buildCall(std::vector<Shared<lang::Value>> arguments, CompileContext& context) const;

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

        [[nodiscard]] virtual Optional<lang::Location> getDefinitionLocation() const = 0;
        [[nodiscard]] virtual bool                     preserveUnitReturn() const    = 0;

        virtual void buildDeclarationsFollowingOrder(CompileContext& context) const;

        [[nodiscard]] virtual lang::BasicBlock const*               getEntryBlock() const;
        [[nodiscard]] virtual std::vector<lang::BasicBlock*> const& getBasicBlocks() const = 0;

        virtual ~FunctionDefinition() = default;

      private:
        lang::Function& function_;
        lang::Scope&    containing_scope_;

        lang::ResolvingHandle<lang::Type>    return_type_;
        lang::Location                       return_type_location_;
        std::vector<Shared<lang::Parameter>> parameters_;
        lang::Location                       location_;

      protected:
        lang::Signature signature_;
    };
}

#endif
