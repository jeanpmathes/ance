#ifndef ANCE_SRC_ANCE_CONSTRUCT_EXTERNFUNCTION_H_
#define ANCE_SRC_ANCE_CONSTRUCT_EXTERNFUNCTION_H_

#include "Function.h"

namespace ance
{
    class ExternFunction : public ance::Function
    {
      public:
        ExternFunction(
            std::string                   function_name,
            ance::Type*                   return_type,
            std::vector<ance::Parameter*> parameters,
            unsigned int                  line,
            unsigned int                  column);

        void buildName(CompileContext* context) override;

        void build(CompileContext* context) override;

        ance::Value* buildCall(const std::vector<ance::Value*>& arguments, CompileContext* context) const override;

      protected:
        using Function::buildCall;

      private:
        std::vector<ance::Parameter*> parameters_;

        llvm::FunctionType* native_type_ {nullptr};
        llvm::Function*     native_function_ {nullptr};
    };
}

#endif
