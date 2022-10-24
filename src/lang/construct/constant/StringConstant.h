#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_STRINGCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_STRINGCONSTANT_H_

#include "Constant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    /**
     * A string constant for the different string representations.
     */
    class StringConstant : public Constant
    {
      public:
        /**
         * Create a new string constant.
         * @param prefix The prefix determining the type.
         * @param string The string content, used directly without any parsing.
         */
        StringConstant(std::string prefix, std::string string);

        [[nodiscard]] std::string toString() const override;

        [[nodiscard]] lang::ResolvingHandle<lang::Type> type() const override;
        llvm::Constant*                                 buildContent(llvm::Module* m) override;

        bool equals(const lang::Constant* other) const override;

        /**
         * Parse a given string to remove quotes and resolve escape sequences.
         * @param unparsed The unparsed string.
         * @return The parsed string.
         */
        static std::string parse(const std::string& unparsed);

      private:
        static lang::ResolvingHandle<lang::Type> resolveType(std::string& prefix, std::string& string);

      private:
        std::string                       prefix_;
        std::string                       literal_;
        std::string                       data_;
        lang::ResolvingHandle<lang::Type> type_;
    };
}

#endif
