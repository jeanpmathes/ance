#ifndef ANCE_SRC_ANCE_CONSTRUCT_FUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_FUNCTION_H_

#include <string>

#include <llvm/IR/DIBuilder.h>
#include <llvm/IR/IRBuilder.h>

#include "ance/construct/Parameter.h"

#include "ance/expression/Expression.h"
#include "compiler/CompileContext.h"

class CompileContext;

namespace ance
{
    class LocalScope;

    class Type;

    class LocalScope;

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
         * @param location The location of the function in the source code.
         */
        Function(std::string function_name, ance::Type* return_type, ance::Location location);

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
         * Get the source location.
         * @return The source location.
         */
        [[nodiscard]] ance::Location location() const;

        /**
         * Build the declaration of this function, allowing it to be called.
         * @param context The current compile context.
         */
        virtual void buildName(CompileContext* context) = 0;
        /**
         * Build the function definition. This will be called after building the name.
         * @param context The current compile context.
         */
        virtual void build(CompileContext* context) = 0;
        /**
         * Build a call to this function.
         * @param arguments The arguments to pass to the function.
         * @param context The current compile context.
         * @return The return value. Will be null for return type void.
         */
        virtual ance::Value* buildCall(const std::vector<ance::Value*>& arguments, CompileContext* context) const = 0;

      protected:
        /**
         * A helper to create a native function.
         * @param parameters The parameters.
         * @param linkage The linkage type.
         * @param c The llvm context.
         * @param m The llvm module.
         * @return The native function type and the native function.
         */
        std::pair<llvm::FunctionType*, llvm::Function*> createNativeFunction(
            const std::vector<ance::Parameter*>& parameters,
            llvm::GlobalValue::LinkageTypes      linkage,
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
        llvm::CallInst* buildCall(const std::vector<ance::Value*>& arguments,
                                  llvm::FunctionType*              native_type,
                                  llvm::Function*                  native_function,
                                  CompileContext*                  context) const;

      private:
        std::string    name_;
        ance::Type*    return_type_;
        ance::Location location_;
    };
}

#endif