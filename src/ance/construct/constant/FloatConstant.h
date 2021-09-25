#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_FLOATCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_FLOATCONSTANT_H_

#include "Constant.h"

namespace ance
{
    class FloatingPointType;
}

namespace ance
{
    /**
     * A floating point constant of any of the floating point types.
     */
    class FloatConstant : public Constant
    {
      public:
        /**
         * Create a new floating point constant.
         * @param number The number to use as value.
         * @param type The type of float to use.
         */
        FloatConstant(llvm::APFloat number, ance::FloatingPointType* type);

        ance::Type*     type() override;
        llvm::Constant* buildContent(llvm::Module* m) override;

      private:
        ance::Type*   type_;
        llvm::APFloat float_;
    };
}

#endif
