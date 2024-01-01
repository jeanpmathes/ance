#include "StringConstant.h"

#include <utility>

#include <boost/locale/encoding_utf.hpp>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/Context.h"
#include "lang/construct/constant/CharConstant.h"
#include "lang/type/ArrayType.h"
#include "lang/type/CharType.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "validation/ValidationLogger.h"

lang::StringConstant::StringConstant(std::string prefix, std::string string, lang::Context& new_context)
    : prefix_(std::move(prefix))
    , literal_(std::move(string))
    , kind_(resolveKind(prefix_, &is_prefix_valid_))
    , data_(createData(literal_, kind_, &is_literal_valid_))
    , type_(resolveType(kind_, data_, new_context))
{}

std::string lang::StringConstant::toString() const
{
    return prefix_ + literal_;
}

lang::ResolvingHandle<lang::Type> lang::StringConstant::type()
{
    return type_;
}

lang::Type const& lang::StringConstant::type() const
{
    return type_;
}

llvm::Constant* lang::StringConstant::createContent(CompileContext& context)
{
    switch (kind_)
    {
        case BYTE:
        {
            auto const& data = std::get<std::string>(data_);
            return context.exec().getByteStringConstant(data);
        }
        case CHAR:
        {
            auto const& data = std::get<std::u32string>(data_);
            return context.exec().getCodepointStringConstant(data);
        }
        case C_STRING:
        {
            auto const&     data        = std::get<std::string>(data_);
            return context.exec().getCStringConstant(data);
        }
    }
}

bool lang::StringConstant::equals(lang::Constant const* other) const
{
    auto other_diff = dynamic_cast<StringConstant const*>(other);
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

lang::StringConstant::Kind lang::StringConstant::resolveKind(std::string const& prefix, bool* valid)
{
    if (prefix.empty()) return CHAR;
    if (prefix == "c") return C_STRING;
    if (prefix == "8") return BYTE;

    *valid = false;
    return CHAR;
}

std::u32string lang::StringConstant::parse(std::u32string const& unparsed, bool* valid)
{
    std::u32string parsed;

    bool escaped = false;

    for (size_t index = 0; index < unparsed.size();)
    {
        if (escaped)
        {
            parsed += lang::CharConstant::readEscapedChar(unparsed, index, *valid);
            escaped = false;
        }
        else
        {
            char32_t const& c = unparsed[index++];

            if (c == '\\') { escaped = true; }
            else if (c != '"') { parsed += c; }
        }
    }

    return parsed;
}

lang::StringConstant::Data lang::StringConstant::createData(std::string const& literal, Kind kind, bool* valid)
{
    std::u32string const unparsed = boost::locale::conv::utf_to_utf<char32_t>(literal);
    std::u32string       parsed   = parse(unparsed, valid);

    switch (kind)
    {
        case CHAR:
            return {parsed};

        case C_STRING:
        case BYTE:
            return {boost::locale::conv::utf_to_utf<char>(parsed)};
    }
}

lang::ResolvingHandle<lang::Type> lang::StringConstant::resolveType(lang::StringConstant::Kind kind,
                                                                    Data const&                data,
                                                                    lang::Context&             new_context)
{
    switch (kind)
    {
        case BYTE:
        {
            size_t const size = std::get<std::string>(data).size();
            return new_context.getArrayType(new_context.getFixedWidthIntegerType(8, false), size);
        }
        case CHAR:
        {
            size_t const size = std::get<std::u32string>(data).size();
            return new_context.getArrayType(new_context.getCharType(), size);
        }
        case C_STRING:
        {
            return new_context.getPointerType(new_context.getFixedWidthIntegerType(8, false));
        }
    }
}

Shared<lang::Constant> lang::StringConstant::clone(lang::Context& new_context) const
{
    return Shared<StringConstant>(*(new StringConstant(prefix_, literal_, new_context)));
}
