#ifndef ANCE_SRC_LANG_CONSTRUCT_FUNCTIONDEFINITION_H_
#define ANCE_SRC_LANG_CONSTRUCT_FUNCTIONDEFINITION_H_

#include <vector>

#include "lang/construct/Parameter.h"
#include "lang/construct/Signature.h"
#include "lang/utility/Location.h"
#include "lang/construct/BasicBlock.h"

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
        explicit FunctionDefinition(lang::Function*                               function,
                                    lang::Scope*                                  containing_scope,
                                    lang::ResolvingHandle<lang::Type>             type,
                                    lang::Location                                return_type_location,
                                    std::vector<std::shared_ptr<lang::Parameter>> parameters,
                                    lang::Location                                location);

        /**
         * Get the name of this function.
         * @return The name.
         */
        [[nodiscard]] const std::string& name() const;

        /**
         * Get the containing scope.
         */
        [[nodiscard]] lang::Scope* scope() const;

        /**
         * Get the function.
         */
        [[nodiscard]] lang::Function* function() const;

        /**
         * Get the return type of this function.
         * @return The return type.
         */
        [[nodiscard]] lang::ResolvingHandle<lang::Type> returnType() const;

        /**
         * Get the function signature.
         * @return The function signature.
         */
        [[nodiscard]] const lang::Signature& signature() const;

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
         * Get whether the name of this function is mangled.
         * @return True if the name is mangled.
         */
        [[nodiscard]] virtual bool isMangled() const = 0;

        /**
         * Validate this function.
         * @param validation_logger A logger to log validation messages.
         */
        virtual void validate(ValidationLogger& validation_logger) = 0;

        /**
         * Add a statement to this function.
         * @param statement The statement to add.
         */
        virtual void pushStatement(std::unique_ptr<Statement> statement) = 0;

        /**
         * Finalize the function definition.
         */
        virtual void finalizeDefinition();

        /**
         * Create the native content of this function, allowing building function code and calling this function.
         * @param context The current compile context.
         */
        virtual void createNativeBacking(CompileContext* context) = 0;

        /**
         * Build the function definition. This will be called after building the name.
         * @param context The current compile context.
         */
        virtual void build(CompileContext* context) = 0;

        /**
         * Validate a call to this function.
         * @param arguments The arguments that will be passed to the function and their source location.
         * @param location The source location of the function call.
         * @param validation_logger A logger to log validation messages.
         * @return True if the call is valid.
         */
        virtual bool validateCall(const std::vector<std::pair<std::shared_ptr<lang::Value>, lang::Location>>& arguments,
                                  lang::Location                                                              location,
                                  ValidationLogger& validation_logger);

        /**
         * Build a call to this function.
         * @param arguments The arguments to pass to the function.
         * @param context The current compile context.
         * @return The return value. Will be null for return type void.
         */
        virtual std::shared_ptr<lang::Value> buildCall(const std::vector<std::shared_ptr<lang::Value>>& arguments,
                                                       CompileContext* context) const = 0;

      protected:
        /**
         * Get the function parameters.
         * @return A vector containing the parameters.
         */
        std::vector<std::shared_ptr<lang::Parameter>>& parameters();

        /**
         * A helper to create a native function.
         * @param linkage The linkage type.
         * @param c The llvm context.
         * @param m The llvm module.
         * @return The native function type and the native function.
         */
        std::pair<llvm::FunctionType*, llvm::Function*> createNativeFunction(llvm::GlobalValue::LinkageTypes linkage,
                                                                             llvm::LLVMContext&              c,
                                                                             llvm::Module*                   m);

        /**
         * A helper to build a call to a native function.
         * @param arguments The arguments to pass to the called function.
         * @param native_type The type of the native function to call.
         * @param native_function The native function to call.
         * @param context The current compile context.
         * @return The return value.
         */
        llvm::CallInst* buildCall(const std::vector<std::shared_ptr<lang::Value>>& arguments,
                                  llvm::FunctionType*                              native_type,
                                  llvm::Function*                                  native_function,
                                  CompileContext*                                  context) const;

      public:
        lang::GlobalScope*        getGlobalScope();
        virtual llvm::DIScope*    getDebugScope(CompileContext* context) = 0;
        virtual lang::LocalScope* getInsideScope()                       = 0;

        virtual ~FunctionDefinition() = default;

      private:
        lang::Function* function_;
        lang::Scope*    containing_scope_;

        lang::ResolvingHandle<lang::Type>             return_type_;
        lang::Location                                return_type_location_;
        std::vector<std::shared_ptr<lang::Parameter>> parameters_;
        lang::Location                                location_;

      protected:
        lang::Signature signature_;
    };
}

#endif
