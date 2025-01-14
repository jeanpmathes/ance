#include "CharConstant.h"

#include <boost/locale/encoding_utf.hpp>

#include "compiler/Application.h"

#include "lang/ApplicationVisitor.h"
#include "lang/type/CharType.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "validation/ValidationLogger.h"

lang::CharConstantData::CharConstantData(std::string const& prefix,
                                         std::string const& content,
                                         lang::Context&     new_context)
    : type_(lang::Type::getUndefined())
    , prefix_(prefix)
    , content_(content)
{
    if (prefix.empty())
    {
        type_.reroute(new_context.getCharType());
        char_ = CharConstant::parseChar(boost::locale::conv::utf_to_utf<char32_t>(content), is_literal_valid_);
    }
    else if (prefix == "8")
    {
        type_.reroute(new_context.getFixedWidthIntegerType(8, false));
        char_ = CharConstant::parseByte(content, is_literal_valid_);
    }
    else { is_prefix_valid_ = false; }
}

lang::CharConstant::CharConstant(std::string const& prefix, std::string const& content, lang::Context& new_context)
    : CharConstantData(prefix, content, new_context)
    , LiteralConstant(CharConstantData::type_)
{}

std::string lang::CharConstant::toString() const
{
    return prefix_ + content_;
}

Shared<lang::Constant> lang::CharConstant::embed(Execution& exec) const
{
    if (type().isCharType()) { return exec.getCodepoint(char_); }

    if (type().isFixedWidthIntegerType(8, false)) { return exec.getByte(static_cast<uint8_t>(char_)); }

    throw std::logic_error("Invalid type for char constant");
}

bool lang::CharConstant::equals(lang::Constant const* other) const
{
    auto other_char = dynamic_cast<CharConstant const*>(other);
    if (!other_char) return false;

    return this->char_ == other_char->char_ && lang::Type::areSame(this->type(), other_char->type());
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

Shared<lang::LiteralConstant> lang::CharConstant::clone(lang::Context& new_context) const
{
    return Shared<CharConstant>(*(new CharConstant(prefix_, content_, new_context)));
}

char32_t lang::CharConstant::parseChar(std::u32string const& unparsed, bool& valid)
{
    Optional<char32_t> content;
    bool               escaped = false;

    for (size_t index = 0; index < unparsed.size();)
    {
        if (content.hasValue() && index != unparsed.size() - 1)
        {
            valid = false;
            return 0;
        }

        if (escaped)
        {
            content = readEscapedChar(unparsed, index, valid);
            escaped = false;
        }
        else
        {
            char32_t const& c = unparsed[index++];

            if (c == '\\') { escaped = true; }
            else if (c != '\'') { content = static_cast<char32_t>(static_cast<unsigned char>(c)); }
        }
    }

    if (!content.hasValue())
    {
        valid = false;
        return 0;
    }

    return content.value();
}

char32_t lang::CharConstant::readEscapedChar(std::u32string const& unparsed, size_t& index, bool& success)
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

        case '\\':
            return '\\';

        case 'u':// Read a unicode code point in the format \u{XXXX}
        {
            if (index >= unparsed.size() || unparsed[index++] != '{')
            {
                success = false;
                return 0;
            }

            std::u32string hex;
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

            std::u32string hex;
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

uint8_t lang::CharConstant::parseByte(std::string const& unparsed, bool& valid)
{
    Optional<uint8_t> content;
    bool              escaped = false;

    for (size_t index = 0; index < unparsed.size(); ++index)
    {
        if (content.hasValue() && index != unparsed.size() - 1)
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

    if (!content.hasValue())
    {
        valid = false;
        return 0;
    }

    return content.value();
}

uint8_t lang::CharConstant::readEscapedByte(std::string const& unparsed, size_t& index, bool& success)
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

        case '\\':
            return '\\';

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
