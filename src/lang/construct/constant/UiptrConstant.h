#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_UIPTRCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_UIPTRCONSTANT_H_

#include "Constant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    /**
     * A uiptr constant for uiptr literals.
     */
    class UiptrConstant : public Constant
    {
      public:
        /**
         * Create a new size constant.
         * @param value The string containing the literal. Must be a hex literal.
         */
        explicit UiptrConstant(std::string value);

        [[nodiscard]] std::string toString() const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        [[nodiscard]] lang::ResolvingHandle<lang::Type> type() const override;
        llvm::Constant*                                 buildContent(llvm::Module* m) override;

        bool equals(const lang::Constant* other) const override;

      private:
        std::string value_;
    };
}

#endif
