#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_BOOLEANCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_BOOLEANCONSTANT_H_

#include "Constant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    /**
     * A constant for boolean values.
     */
    class BooleanConstant : public Constant
    {
      private:
        explicit BooleanConstant(bool boolean);

      public:
        lang::ResolvingHandle<lang::Type> type() override;

        llvm::Constant* buildContent(llvm::Module* m) override;

        /**
         * Create a boolean constant with the false value.
         * @return The new boolean constant.
         */
        static std::shared_ptr<lang::BooleanConstant> createFalse();
        /**
         * Create a boolean constant with the true value.
         * @return The new boolean constant.
         */
        static std::shared_ptr<lang::BooleanConstant> createTrue();

      private:
        lang::ResolvingHandle<lang::Type> type_;
        bool                              boolean_;
    };
}

#endif