#ifndef ANCE_SRC_ANCE_CONSTRUCT_EXTERNFUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_EXTERNFUNCTION_H_

#include "Function.h"

namespace ance
{
    /**
     * A function that is just declared, the actual definition is provided externally when linking.
     */
    class ExternFunction : public ance::Function
    {
      public:
        /**
         * Create a new extern function.
         * @param function_name The function name.
         * @param return_type The return type.
         * @param parameters The parameters.
         * @param location The location of the function declaration.
         */
        ExternFunction(std::string                                   function_name,
                       ance::Type*                                   return_type,
                       std::vector<std::shared_ptr<ance::Parameter>> parameters,
                       ance::Location                                location);

        void validate(ValidationLogger& validation_logger) override;

        void         createNativeBacking(CompileContext* context) override;
        void                         build(CompileContext* context) override;
        std::shared_ptr<ance::Value> buildCall(const std::vector<std::shared_ptr<ance::Value>>& arguments,
                                               CompileContext*                                  context) const override;

      protected:
        using Function::buildCall;

      private:
        llvm::FunctionType* native_type_ {nullptr};
        llvm::Function*     native_function_ {nullptr};
    };
}

#endif
