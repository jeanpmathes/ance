#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_CHARCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_CHARCONSTANT_H_

#include <string>

#include "lang/construct/constant/Constant.h"
#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    class Type;

    /**
     * A constant for different characters.
     */
    class CharConstant : public Constant
    {
      public:
        /**
         * Create a new char constant.
         * @param prefix The prefix of the constant.
         * @param content The content of the constant.
         */
        explicit CharConstant(const std::string& prefix, const std::string& content);

        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] lang::ResolvingHandle<lang::Type> type() const override;
        llvm::Constant*                                 buildContent(llvm::Module* m) override;

        bool equals(const lang::Constant* other) const override;
        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        /**
         * Parse a character from a string.
         * @param unparsed The unparsed string.
         * @param valid Whether the parsing was successful.
         * @return The parsed character.
         */
        static uint32_t parseChar(const std::string& unparsed, bool& valid);

        /**
         * Parse a byte from a string.
         * @param unparsed The unparsed string.
         * @param valid Whether the parsing was successful.
         * @return The parsed byte.
         */
        static uint8_t parseByte(const std::string& unparsed, bool& valid);

        /**
         * Read an escaped character from a string.
         * @param unparsed The unparsed string.
         * @param index The index of the character to read.
         * @param success Whether the read was successful.
         * @return The parsed character.
         */
        static uint32_t readEscapedChar(const std::string& unparsed, size_t& index, bool& success);

        /**
         * Read an escaped character from a string.
         * @param unparsed The unparsed string.
         * @param index The index of the character to read.
         * @param success Whether the read was successful.
         * @return The parsed character.
         */
        static uint8_t readEscapedByte(const std::string& unparsed, size_t& index, bool& success);

      private:
        bool is_literal_valid_ = true;
        bool is_prefix_valid_  = true;

        lang::ResolvingHandle<lang::Type> type_;
        std::string                       prefix_;
        std::string                       content_;
        uint32_t                          char_;
    };
}

#endif

