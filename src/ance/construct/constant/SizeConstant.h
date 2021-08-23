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
         * @param size The string containing the literal.
         * @param app The current application.
         */
        SizeConstant(std::string size, Application& app);

        ance::Type*     type() override;
        llvm::Constant* buildContent(llvm::Module* m) override;

      private:
        Application& app_;
        ance::Type*  type_;
        std::string  size_;
    };
}

#endif
