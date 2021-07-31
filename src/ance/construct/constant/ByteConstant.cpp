#include "ByteConstant.h"

#include <utility>

#include "ance/type/IntegerType.h"
#include "compiler/Application.h"

ance::ByteConstant::ByteConstant(uint8_t byte, Application& app)
    : type_(ance::IntegerType::get(app, 8, false))
    , byte_(byte)
{}

ance::Type* ance::ByteConstant::type()
{
    return type_;
}

llvm::Constant* ance::ByteConstant::buildContent(llvm::Module* m)
{
    return llvm::ConstantInt::get(type_->getNativeType(m->getContext()), byte_, false);
}

char ance::ByteConstant::resolveEscaped(char content)
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

uint8_t ance::ByteConstant::parse(const std::string& unparsed)
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
