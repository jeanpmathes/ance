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
        [[nodiscard]] std::string toString() const override;

        lang::ResolvingHandle<lang::Type> type() override;
        [[nodiscard]] lang::Type const&   type() const override;

        llvm::Constant* createContent(llvm::Module& m) override;

        bool equals(lang::Constant const* other) const override;

        [[nodiscard]] Shared<Constant> clone() const override;

        /**
         * Create a boolean constant with the false value.
         * @return The new boolean constant.
         */
        static Shared<lang::BooleanConstant> createFalse();
        /**
         * Create a boolean constant with the true value.
         * @return The new boolean constant.
         */
        static Shared<lang::BooleanConstant> createTrue();

      private:
        lang::ResolvingHandle<lang::Type> type_;
        bool                              boolean_;
        std::string                       string_;
    };
}

#endif
