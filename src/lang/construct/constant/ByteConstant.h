#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_BYTECONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_BYTECONSTANT_H_

#include <string>

#include "lang/construct/constant/Constant.h"
#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    class Type;

    /**
     * A constant for byte sized values. Can be used for small chars.
     */
    class ByteConstant : public Constant
    {
      public:
        /**
         * Create a new byte constant.
         * @param byte The byte value.
         */
        explicit ByteConstant(uint8_t byte);

        lang::ResolvingHandle<lang::Type> type() override;
        llvm::Constant*                   buildContent(llvm::Module* m) override;

        /**
         * Get the char value for an escaped char.
         * @param content The char after the escape character.
         * @return The value of the escaped char.
         */
        static char resolveEscaped(char content);
        /**
         * Parse a char containing a byte constant.
         * @param unparsed The unparsed string, with quotes and escape characters.
         * @return The value of the contained byte.
         */
        static uint8_t parse(const std::string& unparsed);

      private:
        lang::ResolvingHandle<lang::Type> type_;
        uint8_t                           byte_;
    };
}

#endif
