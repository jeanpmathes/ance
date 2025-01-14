#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_INTEGERCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_INTEGERCONSTANT_H_

#include "LiteralConstant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    class IntegerType;
}

namespace lang
{
    /**
     * An integer constant using any of the integer types.
     */
    class IntegerConstant : public LiteralConstant
    {
      public:
        /**
         * Create a new integer constant.
         * @param integer The integer value to use, encoded as a string.
         * @param radix The radix to use when parsing the integer.
         * @param type The type of the constant. Must be an integer type.
         */
        IntegerConstant(std::string integer, uint8_t radix, lang::ResolvingHandle<lang::Type> type);

        /**
         * Create a new fixed-width integer constant that selects it's size to be large enough to hold the given value.
         * @param integer The integer value to use, encoded as a string. Radix is assumed to be 10.
         * @param is_signed Whether the integer value is signed or unsigned.
         * @param new_context The context to use for the new constant.
         */
        IntegerConstant(std::string const& integer, bool is_signed, lang::Context& new_context);

        [[nodiscard]] std::string toString() const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        Shared<lang::Constant> embed(Execution& exec) const override;

        bool equals(lang::Constant const* other) const override;

        Shared<lang::LiteralConstant> clone(lang::Context& new_context) const override;

      private:
        std::string        text_;
        std::uint8_t       radix_;
        IntegerType const* integer_type_;
    };
}

#endif
