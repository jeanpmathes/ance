#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_FLOATCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_FLOATCONSTANT_H_

#include "Constant.h"

#include "ance/type/FloatingPointType.h"

namespace ance
{
    class FloatConstant : public Constant
    {
      public:
        FloatConstant(llvm::APFloat number, ance::FloatingPointType* type);

        ance::Type* type() override;

        llvm::Constant* buildContent(llvm::Module* m) override;

      private:
        ance::Type*   type_;
        llvm::APFloat float_;
    };
}

#endif
