#include "StringConstant.h"

#include <sstream>

#include "ArrayType.h"
#include "IntegerType.h"

ance::StringConstant::StringConstant(std::string string, ance::Scope* scope)
    : type_(ance::ArrayType::get(scope, ance::IntegerType::get(scope, 8, false), string.size())),
      string_(string), constant_(nullptr)
{

}

ance::Type* ance::StringConstant::get_type()
{
    return type_;
}

llvm::Constant* ance::StringConstant::get_constant(llvm::LLVMContext& c)
{
    if (!constant_)
    {
        constant_ = llvm::ConstantDataArray::getString(c, string_, false);
    }

    return constant_;
}

std::string ance::StringConstant::parse(const std::string& unparsed)
{
    std::stringstream builder;

    bool escaped = false;

    for (char const& c : unparsed)
    {
        if (escaped)
        {
            switch (c)
            {
                case 'n':
                    builder << '\n';
                    break;

                case '0':
                    builder << '\0';
                    break;

                default:
                    builder << c;
                    break;
            }

            escaped = false;
        }
        else
        {
            if (c == '\\')
            {
                escaped = true;
            }
            else if (c != '"')
            {
                builder << c;
            }
        }
    }

    return builder.str();
}
