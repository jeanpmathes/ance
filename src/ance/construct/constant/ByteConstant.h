#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_BYTECONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_BYTECONSTANT_H_

#include <string>

#include "ance/construct/constant/Constant.h"

class Application;

namespace ance
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
         * @param app The current application.
         */
        explicit ByteConstant(uint8_t byte, Application& app);

        ance::Type*     type() override;
        llvm::Constant* buildContent(llvm::Module* m) override;

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
        ance::Type* type_;
        uint8_t     byte_;
    };
}

#endif
