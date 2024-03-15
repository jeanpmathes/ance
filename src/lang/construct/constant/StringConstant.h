#ifndef ANCE_SRC_LANG_CONSTRUCT_CONSTANT_STRINGCONSTANT_H_
#define ANCE_SRC_LANG_CONSTRUCT_CONSTANT_STRINGCONSTANT_H_

#include "LiteralConstant.h"

#include "lang/type/Type.h"
#include "lang/utility/ResolvingHandle.h"

class Application;

namespace lang
{
    class StringConstantData
    {
      public:
        enum Kind
        {
            BYTE,
            CHAR,
            C_STRING
        };

        using Data = std::variant<std::string, std::u32string>;

        StringConstantData(std::string const& prefix, std::string const& literal, lang::Context& context);

        static Kind                              resolveKind(std::string const& prefix, bool* valid);
        static std::u32string                    parse(std::u32string const& unparsed, bool* valid);
        static Data                              createData(std::string const& literal, Kind kind, bool* valid);
        static lang::ResolvingHandle<lang::Type> resolveType(Kind kind, Data const& data, lang::Context& new_context);

        Optional<lang::ResolvingHandle<lang::Type>> type_ = {};

        bool is_prefix_valid_  = true;
        bool is_literal_valid_ = true;

        std::string prefix_;
        std::string literal_;

        Kind kind_ = {};
        Data data_ = {};
    };

    /**
     * A string constant for the different string representations.
     */
    class StringConstant
        : private StringConstantData
        , public LiteralConstant
    {
      public:
        /**
         * Create a new string constant.
         * @param prefix The prefix determining the type.
         * @param string The string content, used directly without any parsing.
         * @param context The context to create the constant in.
         */
        StringConstant(std::string const& prefix, std::string const& string, lang::Context& context);

        [[nodiscard]] std::string toString() const override;

        Shared<lang::Constant> embed(CompileContext& context) const override;

        bool equals(lang::Constant const* other) const override;

        bool validate(ValidationLogger& validation_logger, lang::Location location) const override;

        Shared<lang::LiteralConstant> clone(lang::Context& new_context) const override;
    };
}

#endif
