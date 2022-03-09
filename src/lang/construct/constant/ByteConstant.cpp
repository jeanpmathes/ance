#include "ByteConstant.h"

#include "lang/type/IntegerType.h"
#include "compiler/Application.h"

lang::ByteConstant::ByteConstant(uint8_t byte) : type_(lang::IntegerType::get(8, false)), byte_(byte) {}

std::string lang::ByteConstant::toString() const
{
    std::string escaped = escape(static_cast<char>(byte_));
    return "'" + escaped + "'";
}

lang::ResolvingHandle<lang::Type> lang::ByteConstant::type()
{
    return type_;
}

llvm::Constant* lang::ByteConstant::buildContent(llvm::Module* m)
{
    return llvm::ConstantInt::get(type_->getContentType(m->getContext()), byte_, false);
}

char lang::ByteConstant::resolveEscaped(char content)
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

std::string lang::ByteConstant::escape(char content)
{
    std::string escaped;

    switch (content)
    {
        case '\n':
            escaped = "\\n";
            break;

        case '\0':
            escaped = "\\0";
            break;

        default:
            escaped = std::string(1, content);
            break;
    }

    return escaped;
}

uint8_t lang::ByteConstant::parse(const std::string& unparsed)
{
    uint8_t byte;
    bool    escaped = false;

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
            else if (c != '\'')
            {
                byte = c;
            }
        }
    }

    return byte;
}
