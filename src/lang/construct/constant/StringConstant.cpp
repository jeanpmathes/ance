#include "StringConstant.h"

#include <sstream>
#include <utility>

#include "lang/construct/constant/CharConstant.h"
#include "lang/type/ArrayType.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/PointerType.h"
#include "validation/ValidationLogger.h"

lang::StringConstant::StringConstant(std::string prefix, std::string string)
    : prefix_(std::move(prefix))
    , literal_(std::move(string))
    , data_(parse(literal_, is_literal_valid_))
    , type_(resolveType(prefix_, data_, is_prefix_valid_))
{
    is_literal_valid_ &= true;
    is_prefix_valid_ &= true;
}

std::string lang::StringConstant::toString() const
{
    return prefix_ + literal_;
}

lang::ResolvingHandle<lang::Type> lang::StringConstant::type() const
{
    return type_;
}

llvm::Constant* lang::StringConstant::buildContent(llvm::Module* m)
{
    if (prefix_ == "c")
    {
        llvm::Constant* content     = llvm::ConstantDataArray::getString(m->getContext(), data_, true);
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
    else { return llvm::ConstantDataArray::getString(m->getContext(), data_, false); }
}

bool lang::StringConstant::equals(const lang::Constant* other) const
{
    auto other_diff = dynamic_cast<const StringConstant*>(other);
    if (!other_diff) return false;

    return this->prefix_ == other_diff->prefix_ && this->data_ == other_diff->data_;
}

bool lang::StringConstant::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    if (!is_prefix_valid_)
    {
        validation_logger.logError("Invalid string prefix: " + prefix_, location);
        return false;
    }

    if (!is_literal_valid_)
    {
        validation_logger.logError("Invalid string literal: " + literal_, location);
        return false;
    }

    return true;
}

std::string lang::StringConstant::parse(const std::string& unparsed, bool& valid)
{
    std::stringstream builder;

    bool escaped = false;

    for (size_t index = 0; index < unparsed.size(); ++index)
    {
        char const& c = unparsed[index];

        if (escaped)
        {
            builder << lang::CharConstant::readEscapedByte(unparsed, index, valid);
            escaped = false;
        }
        else if (c == '\\') { escaped = true; }
        else if (c != '"') { builder << c; }
    }

    return builder.str();
}

lang::ResolvingHandle<lang::Type> lang::StringConstant::resolveType(std::string& prefix,
                                                                    std::string& string,
                                                                    bool&        valid)
{
    if (prefix.empty()) return lang::ArrayType::get(lang::FixedWidthIntegerType::get(8, false), string.size());
    if (prefix == "c") return lang::PointerType::get(lang::FixedWidthIntegerType::get(8, false));

    valid = false;
    return lang::PointerType::get(lang::FixedWidthIntegerType::get(8, false));
}
