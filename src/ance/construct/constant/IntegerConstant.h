#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_INTEGERCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_INTEGERCONSTANT_H_

#include "Constant.h"

#include "compiler/Application.h"

namespace ance
{
    /**
     * An integer constant using any of the integer types.
     */
    class IntegerConstant : public Constant
    {
      public:
        /**
         * Create a new integer constant.
         * @param integer The integer value to use. The bit width determines the used type.
         * @param is_signed Whether the integer should be signed or unsigned.
         * @param app The current application.
         */
        IntegerConstant(llvm::APInt integer, bool is_signed, Application& app);

        ance::Type* type() override;
        llvm::Constant* buildContent(llvm::Module* m) override;

      private:
        ance::Type* type_;
        llvm::APInt integer_;
    };
}

#endif
