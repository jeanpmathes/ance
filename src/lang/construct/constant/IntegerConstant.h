#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_INTEGERCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_INTEGERCONSTANT_H_

#include "Constant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    /**
     * An integer constant using any of the integer types.
     */
    class IntegerConstant : public Constant
    {
      public:
        /**
         * Create a new integer constant.
         * @param integer The integer value to use, encoded as a string.
         * @param size The size of the integer, in bits.
         * @param is_signed Whether the integer should be signed or unsigned.
         * @param radix The radix to use when parsing the integer.
         */
        IntegerConstant(std::string integer, int64_t size, bool is_signed, int radix = 10);

        /**
         * Create a new integer constant that selects it's size to be large enough to hold the given value.
         * @param integer The integer value to use, encoded as a string. Radix is assumed to be 10.
         * @param is_signed Whether the integer value is signed or unsigned.
         */
        IntegerConstant(const std::string& integer, bool is_signed);

        [[nodiscard]] std::string toString() const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        lang::ResolvingHandle<lang::Type> type() const override;
        llvm::Constant*                   buildContent(llvm::Module* m) override;

        bool equals(const lang::Constant* other) const override;

      private:
        std::string                       text_;
        std::int64_t                      size_;
        int                               radix_;
        lang::ResolvingHandle<lang::Type> type_;
    };
}

#endif
