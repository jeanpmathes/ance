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

        lang::ResolvingHandle<lang::Type> type() override;
        [[nodiscard]] lang::Type const&   type() const override;

        llvm::Constant* createContent(llvm::Module* m) override;

        bool equals(lang::Constant const* other) const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        Shared<Constant> clone() const override;

      private:
        enum Kind
        {
            BYTE,
            CHAR,
            C_STRING
        };

        using Data = std::variant<std::string, std::u32string>;

      private:
        static Kind                              resolveKind(std::string const& prefix, bool* valid);
        static std::u32string                    parse(std::u32string const& unparsed, bool* valid);
        static Data                              createData(std::string const& literal, Kind kind, bool* valid);
        static lang::ResolvingHandle<lang::Type> resolveType(Kind kind, Data const& data);

      private:
        bool is_prefix_valid_  = true;
        bool is_literal_valid_ = true;

        std::string prefix_;
        std::string literal_;

        Kind                              kind_;
        Data                              data_;
        lang::ResolvingHandle<lang::Type> type_;
    };
}

#endif
