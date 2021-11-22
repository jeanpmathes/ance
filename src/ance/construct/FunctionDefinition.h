#ifndef ANCE_SRC_ANCE_CONSTRUCT_FUNCTIONDEFINITION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_FUNCTIONDEFINITION_H_

#include <vector>

#include "ance/construct/Parameter.h"
#include "ance/utility/Location.h"

namespace ance
{
    class Variable;
    class Scope;
    class GlobalScope;
    class LocalScope;
    class Function;
}

class Statement;
class ValidationLogger;

namespace ance
{
    class FunctionDefinition
    {
      public:
        explicit FunctionDefinition(ance::Function*                               function,
                                    ance::Scope*                                  containing_scope,
                                    ance::ResolvingHandle<ance::Type>             type,
                                    ance::Location                                return_type_location,
                                    std::vector<std::shared_ptr<ance::Parameter>> parameters,
                                    ance::Location                                location);

        /**
         * Get the name of this function.
         * @return The name.
         */
        [[nodiscard]] const std::string& name() const;

        /**
         * Get the containing scope.
         */
        [[nodiscard]] ance::Scope* scope() const;

        /**
         * Get the function.
         */
        [[nodiscard]] ance::Function* function() const;

        /**
         * Get the return type of this function.
         * @return The return type.
         */
        [[nodiscard]] ance::ResolvingHandle<ance::Type> returnType() const;

        /**
         * Get the location of the return type.
         * @return The location.
         */
        [[nodiscard]] ance::Location returnTypeLocation() const;

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
         * Validate this function.
         * @param validation_logger A logger to log validation messages.
         */
        virtual void validate(ValidationLogger& validation_logger) = 0;

        /**
         * Push a statement to the end of the statement list.
         * @param statement The statement to add.
         */
        virtual void pushStatement(Statement* statement) = 0;

        /**
         * Add a return. Call this method in the build method of a statement.
         * @param value The value to return or nullptr if nothing is returned.
         */
        virtual void addReturn(const std::shared_ptr<ance::Value>& value) = 0;

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
        llvm::CallInst* buildCall(const std::vector<std::shared_ptr<ance::Value>>& arguments,
                                  llvm::FunctionType*                              native_type,
                                  llvm::Function*                                  native_function,
                                  CompileContext*                                  context) const;

      public:
        ance::GlobalScope* getGlobalScope();
        virtual llvm::DIScope*  getDebugScope(CompileContext* context)         = 0;
        virtual ance::LocalScope* getInsideScope() = 0;

        virtual ~FunctionDefinition() = default;

      private:
        ance::Function* function_;
        ance::Scope*    containing_scope_;

        ance::ResolvingHandle<ance::Type>             return_type_;
        ance::Location                                return_type_location_;
        std::vector<std::shared_ptr<ance::Parameter>> parameters_;
        ance::Location                                location_;
    };
}

#endif
