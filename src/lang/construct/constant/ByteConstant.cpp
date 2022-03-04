#include "ByteConstant.h"

#include "lang/type/IntegerType.h"
#include "compiler/Application.h"

lang::ByteConstant::ByteConstant(uint8_t byte) : type_(lang::IntegerType::get(8, false)), byte_(byte) {}

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