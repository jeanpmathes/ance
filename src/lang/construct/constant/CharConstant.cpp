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

    return static_cast<uint32_t>(byte);
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
