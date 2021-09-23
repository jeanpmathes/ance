#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_SIZECONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_SIZECONSTANT_H_

#include "Constant.h"

class Application;

namespace ance
{
    /**
     * A size constant for size literals.
     */
    class SizeConstant : public Constant
    {
      public:
        /**
         * Create a new size constant.
         * @param value The string containing the literal.
         */
        explicit SizeConstant(std::string value);

        ance::Type*     type() override;
        llvm::Constant* buildContent(llvm::Module* m) override;

      private:
        ance::Type* type_;
        std::string value_;
    };
}

#endif
