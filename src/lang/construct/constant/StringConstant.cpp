#include "StringConstant.h"

#include <sstream>

#include "lang/construct/constant/ByteConstant.h"
#include "lang/type/ArrayType.h"
#include "lang/type/IntegerType.h"
#include "lang/type/PointerType.h"

lang::StringConstant::StringConstant(std::string prefix, std::string string)
    : type_(resolveType(prefix, string))
    , prefix_(prefix)
    , string_(string)
{}

std::string lang::StringConstant::toString() const
{
    std::string escaped;

    for (auto& c : string_) { escaped += lang::ByteConstant::escape(c); }

    return prefix_ + "\"" + escaped + "\"";
}

lang::ResolvingHandle<lang::Type> lang::StringConstant::type() const
{
    return type_;
}

llvm::Constant* lang::StringConstant::buildContent(llvm::Module* m)
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
    else {
        return llvm::ConstantDataArray::getString(m->getContext(), string_, false);
    }
}

bool lang::StringConstant::equals(const lang::Constant* other) const
{
    auto other_diff = dynamic_cast<const StringConstant*>(other);
    if (!other_diff) return false;

    return this->prefix_ == other_diff->prefix_ && this->string_ == other_diff->string_;
}

std::string lang::StringConstant::parse(const std::string& unparsed)
{
    std::stringstream builder;

    bool escaped = false;

    for (char const& c : unparsed)
    {
        if (escaped)
        {
            builder << lang::ByteConstant::resolveEscaped(c);
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

lang::ResolvingHandle<lang::Type> lang::StringConstant::resolveType(std::string& prefix, std::string& string)
{
    if (prefix == "c") { return lang::PointerType::get(lang::IntegerType::get(8, false)); }

    return lang::ArrayType::get(lang::IntegerType::get(8, false), string.size());
}
