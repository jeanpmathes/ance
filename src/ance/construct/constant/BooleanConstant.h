#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_BOOLEANCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_BOOLEANCONSTANT_H_

#include "Constant.h"

class Application;

namespace ance
{
    /**
     * A constant for boolean values.
     */
    class BooleanConstant : public Constant
    {
      private:
        explicit BooleanConstant(bool boolean);

      public:
        ance::Type* type() override;

        llvm::Constant* buildContent(llvm::Module* m) override;

        /**
         * Create a boolean constant with the false value.
         * @return The new boolean constant.
         */
        static std::shared_ptr<ance::BooleanConstant> createFalse();
        /**
         * Create a boolean constant with the true value.
         * @return The new boolean constant.
         */
        static std::shared_ptr<ance::BooleanConstant> createTrue();

      private:
        ance::Type* type_;
        bool        boolean_;
    };
}

#endif
