#ifndef ANCE_SRC_ANCE_CONSTRUCT_FUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_FUNCTION_H_

#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/construct/Parameter.h"

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
     * The abstract base class of all functions.
     */
    class Function
    {
      public:
        /**
         * Create a new function.
         * @param function_name The function name.
         * @param return_type The return type of the function.
         * @param parameters The function parameters.
         * @param location The location of the function in the source code.
         */
        Function(std::string                                   function_name,
                 ance::Type*                                   return_type,
                 std::vector<std::shared_ptr<ance::Parameter>> parameters,
                 ance::Location                                location);

        /**
         * Get the name of this function.
         * @return The name.
         */
        [[nodiscard]] std::string name() const;

        /**
         * Get the return type of this function.
         * @return The return type.
         */
        [[nodiscard]] ance::Type* returnType() const;

        /**
         * Get the type of a parameter.
         * @param index The index of the parameter. Must be smaller than the parameter count.
         * @return The type of the selected parameter.
         */
        [[nodiscard]] ance::Type* parameterType(size_t index) const;

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
         * Validate this function.
         * @param validation_logger A logger to log validation messages.
         */
        virtual void validate(ValidationLogger& validation_logger) = 0;

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
        virtual bool validateCall(const std::vector<std::pair<std::shared_ptr<ance::Value>, ance::Location>>& arguments,
                                  ance::Location                                                              location,
                                  ValidationLogger& validation_logger);

        /**
         * Build a call to this function.
         * @param arguments The arguments to pass to the function.
         * @param context The current compile context.
         * @return The return value. Will be null for return type void.
         */
        virtual std::shared_ptr<ance::Value> buildCall(const std::vector<std::shared_ptr<ance::Value>>& arguments,
                                                       CompileContext* context) const = 0;

        virtual ~Function() = default;

      protected:
        /**
         * Get the function parameters.
         * @return A vector containing the parameters.
         */
        std::vector<std::shared_ptr<ance::Parameter>>& parameters();

        /**
         * A helper to create a native function.
         * @param linkage The linkage type.
         * @param c The llvm context.
         * @param m The llvm module.
         * @return The native function type and the native function.
         */
        std::pair<llvm::FunctionType*, llvm::Function*> createNativeFunction(llvm::GlobalValue::LinkageTypes linkage,
                                                                             llvm::LLVMContext&                   c,
            llvm::Module*                        m);

        /**
         * A helper to build a call to a native function.
         * @param arguments The arguments to pass to the called function.
         * @param native_type The type of the native function to call.
         * @param native_function The native function to call.
         * @param context The current compile context.
         * @return The return value.
         */
        llvm::CallInst* buildCall(const std::vector<std::shared_ptr<ance::Value>>& arguments,
                                  llvm::FunctionType*                              native_type,
                                  llvm::Function*                                  native_function,
                                  CompileContext*                                  context) const;

      private:
        std::string                                   name_;
        ance::Type*                                   return_type_;
        std::vector<std::shared_ptr<ance::Parameter>> parameters_;
        ance::Location                                location_;
    };
}

#endif