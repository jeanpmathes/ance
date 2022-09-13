#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_SIZECONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_SIZECONSTANT_H_

#include "Constant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
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

        [[nodiscard]] std::string toString() const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        lang::ResolvingHandle<lang::Type> type() const override;
        llvm::Constant*                   buildContent(llvm::Module* m) override;

        bool equals(const lang::Constant* other) const override;

      private:
        lang::ResolvingHandle<lang::Type> type_;
        std::string                       value_;
    };
}

#endif

