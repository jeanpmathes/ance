#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_NULLCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_NULLCONSTANT_H_

#include "Constant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    /**
     * The constant null (pointer).
     */
    class NullConstant : public Constant
    {
      public:
        NullConstant();

        [[nodiscard]] std::string toString() const override;

        lang::ResolvingHandle<lang::Type> type() override;
        [[nodiscard]] lang::Type const&   type() const override;

        llvm::Constant* createContent(llvm::Module* m) override;

        bool equals(lang::Constant const* other) const override;

        Shared<Constant> clone() const override;

        /**
         * Create a null constant.
         * @return The new null constant.
         */
        static Shared<lang::NullConstant> create();

      private:
        lang::ResolvingHandle<lang::Type> type_;
    };
}

#endif
