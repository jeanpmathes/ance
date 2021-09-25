#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_DIFFCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_DIFFCONSTANT_H_

#include "Constant.h"

class Application;

namespace ance
{
    /**
     * An integer constant for diff literals.
     */
    class DiffConstant : public Constant
    {
      public:
        /**
         * Create a new size constant.
         * @param value The string containing the literal value.
         */
        explicit DiffConstant(std::string value);

        ance::Type*     type() override;
        llvm::Constant* buildContent(llvm::Module* m) override;

      private:
        ance::Type* type_;
        std::string value_;
    };
}

#endif
