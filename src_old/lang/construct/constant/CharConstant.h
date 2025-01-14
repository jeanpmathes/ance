#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_CHARCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_CHARCONSTANT_H_

#include <string>

#include "LiteralConstant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    class Type;

    class CharConstantData
    {
      public:
        CharConstantData(std::string const& prefix, std::string const& content, lang::Context& new_context);

        lang::ResolvingHandle<lang::Type> type_;

        bool is_literal_valid_ = true;
        bool is_prefix_valid_  = true;

        std::string prefix_;
        std::string content_;
        char32_t    char_;
    };

    /**
     * A constant for different characters.
     */
    class CharConstant
        : private CharConstantData
        , public LiteralConstant
    {
      public:
        /**
         * Create a new char constant.
         * @param prefix The prefix of the constant.
         * @param content The content of the constant.
         * @param new_context The context to create the constant in.
         */
        CharConstant(std::string const& prefix, std::string const& content, lang::Context& new_context);

        [[nodiscard]] std::string toString() const override;

        Shared<lang::Constant> embed(Execution& exec) const override;

        bool equals(lang::Constant const* other) const override;
        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        Shared<lang::LiteralConstant> clone(lang::Context& new_context) const override;

        /**
         * Parse a character from a string.
         * @param unparsed The unparsed string.
         * @param valid Whether the parsing was successful.
         * @return The parsed character.
         */
        static char32_t parseChar(std::u32string const& unparsed, bool& valid);

        /**
         * Parse a byte from a string.
         * @param unparsed The unparsed string.
         * @param valid Whether the parsing was successful.
         * @return The parsed byte.
         */
        static uint8_t parseByte(std::string const& unparsed, bool& valid);

        /**
         * Read an escaped character from a string.
         * @param unparsed The unparsed string.
         * @param index The index of the character to read.
         * @param success Whether the read was successful.
         * @return The parsed character.
         */
        static char32_t readEscapedChar(std::u32string const& unparsed, size_t& index, bool& success);

        /**
         * Read an escaped character from a string.
         * @param unparsed The unparsed string.
         * @param index The index of the character to read.
         * @param success Whether the read was successful.
         * @return The parsed character.
         */
        static uint8_t readEscapedByte(std::string const& unparsed, size_t& index, bool& success);
    };
}

#endif
