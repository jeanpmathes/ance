#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_NULLCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_NULLCONSTANT_H_

#include "Constant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    /**
     * A constant for boolean values.
     */
    class NullConstant : public Constant
    {
      public:
        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] lang::ResolvingHandle<lang::Type> type() const override;

        llvm::Constant* buildContent(llvm::Module* m) override;

        bool equals(const lang::Constant* other) const override;

        /**
         * Create a null constant.
         * @return The new null constant.
         */
        static std::shared_ptr<lang::NullConstant> create();
    };
}

#endif
