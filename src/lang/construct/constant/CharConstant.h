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

        /**
         * Parse a character from a string.
         * @param unparsed The unparsed string.
         * @return The parsed character.
         */
        static uint32_t parseChar(const std::string& unparsed);

        /**
         * Parse a byte from a string.
         * @param unparsed The unparsed string.
         * @return The parsed byte.
         */
        static uint8_t parseByte(const std::string& unparsed);

        /**
         * Read an escaped character from a string.
         * @param unparsed The unparsed string.
         * @param index The index of the character to read.
         * @param success Whether the read was successful.
         * @return The parsed character.
         */
        static uint32_t readEscaped(const std::string& unparsed, size_t& index, bool& success);

        /**
         * Get the char value for an escaped char.
         * @param c The char after the escape character.
         * @return The value of the escaped char.
         */
        static char resolveEscaped(char c);

      private:
        lang::ResolvingHandle<lang::Type> type_;
        std::string                       prefix_;
        std::string                       content_;
        uint32_t                          char_;
    };
}

#endif

