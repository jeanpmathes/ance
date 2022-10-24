#include "CharConstant.h"

#include "compiler/Application.h"
#include "lang/ApplicationVisitor.h"
#include "lang/type/CharType.h"
#include "lang/type/FixedWidthIntegerType.h"

lang::CharConstant::CharConstant(const std::string& prefix, const std::string& content)
    : type_(lang::Type::getUndefined())
    , prefix_(prefix)
    , content_(content)
    , char_(0)
{
    if (prefix.empty())
    {
        type_ = lang::CharType::get();
        char_ = parseChar(content);
    }
    else if (prefix == "8")
    {
        type_ = lang::FixedWidthIntegerType::get(8, false);
        char_ = parseByte(content);
    }
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
    auto other_byte = dynamic_cast<const CharConstant*>(other);
    if (!other_byte) return false;

    return this->char_ == other_byte->char_ && lang::Type::areSame(this->type_, other_byte->type_);
}

uint32_t lang::CharConstant::parseChar(const std::string& unparsed)
{
    uint32_t content = 0;
    bool     escaped = false;

    bool s;

    for (size_t index = 0; index < unparsed.size(); ++index)
    {
        char const& c = unparsed[index];

        if (escaped)
        {
            content = readEscaped(unparsed, index, s);
            escaped = false;
        }
        else if (c == '\\') { escaped = true; }
        else if (c != '\'') { content = static_cast<uint32_t>(static_cast<unsigned char>(c)); }
    }

    return content;
}

uint32_t lang::CharConstant::readEscaped(const std::string& unparsed, size_t& index, bool& success)
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

        case 'u':// Read a unicode code point in the format \u{XXXX}
        {
            if (unparsed[index++] != '{')
            {
                success = false;
                return 0;
            }

            std::string hex;
            while (unparsed[index] != '}') { hex += unparsed[index++]; }

            if (unparsed[index++] != '}')
            {
                success = false;
                return 0;
            }

            return static_cast<uint32_t>(std::stoul(hex, nullptr, 16));
        }

        default:
            return static_cast<uint32_t>(static_cast<unsigned char>(c));
    }
}

uint8_t lang::CharConstant::parseByte(const std::string& unparsed)
{
    char byte    = 0;
    bool escaped = false;

    for (char const& c : unparsed)
    {
        if (escaped)
        {
            byte    = resolveEscaped(c);
            escaped = false;
        }
        else
        {
            if (c == '\\') { escaped = true; }
            else if (c != '\'') { byte = c; }
        }
    }

    return static_cast<uint8_t>(byte);
}

char lang::CharConstant::resolveEscaped(char content)
{
    switch (content)
    {
        case 'n':
            return '\n';

        case '0':
            return '\0';

        default:
            return content;
    }
}
