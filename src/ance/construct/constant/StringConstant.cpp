#include "StringConstant.h"

#include <sstream>

#include "ance/construct/constant/ByteConstant.h"
#include "ance/type/ArrayType.h"
#include "ance/type/IntegerType.h"
#include "ance/type/PointerType.h"

ance::StringConstant::StringConstant(std::string prefix, std::string string, Application& app)
    : type_(resolveType(prefix, string, app))
    , prefix_(prefix)
    , string_(string)
{}

ance::Type* ance::StringConstant::type()
{
    return type_;
}

llvm::Constant* ance::StringConstant::buildContent(llvm::Module* m)
{
    if (prefix_ == "c")
    {
        llvm::Constant* content     = llvm::ConstantDataArray::getString(m->getContext(), string_, true);
        auto*           str_arr_ptr = new llvm::GlobalVariable(*m,
                                                     content->getType(),
                                                     true,
                                                     llvm::GlobalValue::PrivateLinkage,
                                                     content,
                                                     "data.str");

        llvm::Constant* zero      = llvm::ConstantInt::get(llvm::Type::getInt64Ty(m->getContext()), 0);
        llvm::Constant* indices[] = {zero, zero};

        return llvm::ConstantExpr::getInBoundsGetElementPtr(str_arr_ptr->getValueType(), str_arr_ptr, indices);
    }
    else
    {
        return llvm::ConstantDataArray::getString(m->getContext(), string_, false);
    }
}

std::string ance::StringConstant::parse(const std::string& unparsed)
{
    std::stringstream builder;

    bool escaped = false;

    for (char const& c : unparsed)
    {
        if (escaped)
        {
            builder << ance::ByteConstant::resolveEscaped(c);
            escaped = false;
        }
        else
        {
            if (c == '\\') { escaped = true; }
            else if (c != '"')
            {
                builder << c;
            }
        }
    }

    return builder.str();
}

ance::Type* ance::StringConstant::resolveType(std::string& prefix, std::string& string, Application& app)
{
    if (prefix == "c") { return ance::PointerType::get(app, ance::IntegerType::get(app, 8, false)); }

    return ance::ArrayType::get(ance::IntegerType::get(app, 8, false), string.size());
}
