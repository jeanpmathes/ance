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
        explicit BooleanConstant(bool boolean, Application& app);

      public:
        ance::Type* type() override;

        llvm::Constant* buildContent(llvm::Module* m) override;

        /**
         * Create a boolean constant with the false value.
         * @param app The current application.
         * @return The new boolean constant.
         */
        static ance::BooleanConstant* createFalse(Application& app);
        /**
         * Create a boolean constant with the true value.
         * @param app The current application.
         * @return The new boolean constant.
         */
        static ance::BooleanConstant* createTrue(Application& app);

      private:
        ance::Type* type_;
        bool        boolean_;
    };
}

#endif
