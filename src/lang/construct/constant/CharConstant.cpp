#include "CharConstant.h"

#include <boost/locale/encoding_utf.hpp>

#include "compiler/Application.h"
#include "lang/ApplicationVisitor.h"
#include "lang/type/CharType.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "validation/ValidationLogger.h"

lang::CharConstant::CharConstant(const std::string& prefix, const std::string& content)
    : type_(lang::CharType::get())
    , prefix_(prefix)
    , content_(content)
    , char_(0)
{
    if (prefix.empty())
    {
        type_ = lang::CharType::get();
        char_ = parseChar(boost::locale::conv::utf_to_utf<char32_t>(content), is_literal_valid_);
    }
    else if (prefix == "8")
    {
        type_ = lang::FixedWidthIntegerType::get(8, false);
        char_ = parseByte(content, is_literal_valid_);
    }
    else { is_prefix_valid_ = false; }
}

std::string lang::CharConstant::toString() const
{
    return prefix_ + "'" + content_ + "'";
}

lang::ResolvingHandle<lang::Type> lang::CharConstant::type() const
{
    return type_;
}

llvm::Constant* lang::CharConstant::buildContent(llvm::Module* m)
{
    return llvm::ConstantInt::get(type_->getContentType(m->getContext()), char_, false);
}

bool lang::CharConstant::equals(const lang::Constant* other) const
{
    auto other_char = dynamic_cast<const CharConstant*>(other);
    if (!other_char) return false;

    return this->char_ == other_char->char_ && lang::Type::areSame(this->type_, other_char->type_);
}

bool lang::CharConstant::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    if (!is_prefix_valid_)
    {
        validation_logger.logError("Invalid character prefix: " + prefix_, location);
        return false;
    }

    if (!is_literal_valid_)
    {
        validation_logger.logError("Invalid character literal: " + content_, location);
        return false;
    }

    return true;
}

char32_t lang::CharConstant::parseChar(const std::basic_string<char32_t>& unparsed, bool& valid)
{
    std::optional<char32_t> content;
    bool                    escaped = false;

    for (size_t index = 0; index < unparsed.size(); ++index)
    {
        if (content.has_value() && index != unparsed.size() - 1)
        {
            valid = false;
            return 0;
        }

        char32_t const& c = unparsed[index];

        if (escaped)
        {
            content = readEscapedChar(unparsed, index, valid);
            escaped = false;
        }
        else if (c == '\\') { escaped = true; }
        else if (c != '\'') { content = static_cast<char32_t>(static_cast<unsigned char>(c)); }
    }

    if (!content.has_value())
    {
        valid = false;
        return 0;
    }

    return content.value();
}

char32_t lang::CharConstant::readEscapedChar(const std::basic_string<char32_t>& unparsed, size_t& index, bool& success)
{
    char32_t const& c = unparsed[index++];
    switch (c)
    {
        case 'n':
            return '\n';

        case '0':
            return '\0';

        case 't':
            return '\t';

        case 'r':
            return '\r';

        case 'v':
            return '\v';

        case 'b':
            return '\b';

        case 'a':
            return '\a';

        case 'f':
            return '\f';

        case 'u':// Read a unicode code point in the format \u{XXXX}
        {
            if (index >= unparsed.size() || unparsed[index++] != '{')
            {
                success = false;
                return 0;
            }

            std::basic_string<char32_t> hex;
            while (index < unparsed.size() && unparsed[index] != '}') { hex += unparsed[index++]; }

            if (index >= unparsed.size() || unparsed[index++] != '}')
            {
                success = false;
                return 0;
            }

            try
            {
                return static_cast<char32_t>(std::stoul(boost::locale::conv::utf_to_utf<char>(hex), nullptr, 16));
            }
            catch (std::invalid_argument&)
            {
                success = false;
                return 0;
            }
            catch (std::out_of_range&)
            {
                success = false;
                return 0;
            }
        }

        case 'x':// Read a hex 8-byte character with the format \xXX
        {
            if (unparsed.size() - index < 2)
            {
                success = false;
                return 0;
            }

            std::basic_string<char32_t> hex;
            hex += unparsed[index++];
            hex += unparsed[index++];

            try
            {
                return static_cast<uint8_t>(std::stoul(boost::locale::conv::utf_to_utf<char>(hex), nullptr, 16));
            }
            catch (std::invalid_argument&)
            {
                success = false;
                return 0;
            }
            catch (std::out_of_range&)
            {
                success = false;
                return 0;
            }
        }

        default:
            return static_cast<uint32_t>(static_cast<unsigned char>(c));
    }
}

uint8_t lang::CharConstant::parseByte(const std::string& unparsed, bool& valid)
{
    std::optional<uint8_t> content;
    bool                   escaped = false;

    for (size_t index = 0; index < unparsed.size(); ++index)
    {
        if (content.has_value() && index != unparsed.size() - 1)
        {
            valid = false;
            return 0;
        }

        char const& c = unparsed[index];

        if (escaped)
        {
            content = readEscapedByte(unparsed, index, valid);
            escaped = false;
        }
        else if (c == '\\') { escaped = true; }
        else if (c != '\'') { content = static_cast<uint8_t>(static_cast<unsigned char>(c)); }
    }

    if (!content.has_value())
    {
        valid = false;
        return 0;
    }

    return content.value();
}

uint8_t lang::CharConstant::readEscapedByte(const std::string& unparsed, size_t& index, bool& success)
{
    char const& c = unparsed[index++];
    switch (c)
    {
        case 'n':
            return '\n';

        case '0':
            return '\0';

        case 't':
            return '\t';

        case 'r':
            return '\r';

        case 'v':
            return '\v';

        case 'b':
            return '\b';

        case 'a':
            return '\a';

        case 'f':
            return '\f';

        case 'x':// Read a hex 8-byte character with the format \xXX
        {
            if (unparsed.size() - index < 2)
            {
                success = false;
                return 0;
            }

            std::string hex;
            hex += unparsed[index++];
            hex += unparsed[index++];

            try
            {
                return static_cast<uint8_t>(std::stoul(hex, nullptr, 16));
            }
            catch (std::invalid_argument&)
            {
                success = false;
                return 0;
            }
            catch (std::out_of_range&)
            {
                success = false;
                return 0;
            }
        }

        default:
            return static_cast<uint8_t>(static_cast<unsigned char>(c));
    }
}
