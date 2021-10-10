#ifndef ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_STRINGCONSTANT_H_
#define ANCE_SRC_ANCE_CONSTRUCT_CONSTANT_STRINGCONSTANT_H_

#include "Constant.h"

class Application;

namespace ance
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

        ance::Type*     type() override;
        llvm::Constant* buildContent(llvm::Module* m) override;

        /**
         * Parse a given string to remove quotes and resolve escape sequences.
         * @param unparsed The unparsed string.
         * @return The parsed string.
         */
        static std::string parse(const std::string& unparsed);

      private:
        static ance::Type* resolveType(std::string& prefix, std::string& string);

      private:
        ance::Type* type_;
        std::string prefix_;
        std::string string_;
    };
}

#endif
