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

lang::StringConstantData::StringConstantData(std::string const& prefix,
                                             std::string const& literal,
                                             lang::Context&     context)
    : prefix_(prefix)
    , literal_(literal)
{
    kind_ = resolveKind(prefix, &is_prefix_valid_);
    data_ = createData(literal, kind_, &is_literal_valid_);
    type_ = resolveType(kind_, data_, context);
}

lang::StringConstantData::Kind lang::StringConstantData::resolveKind(std::string const& prefix, bool* valid)
{
    if (prefix.empty()) return CHAR;
    if (prefix == "c") return C_STRING;
    if (prefix == "8") return BYTE;

    *valid = false;
    return CHAR;
}

std::u32string lang::StringConstantData::parse(std::u32string const& unparsed, bool* valid)
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

lang::StringConstantData::Data lang::StringConstantData::createData(std::string const& literal, Kind kind, bool* valid)
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

lang::ResolvingHandle<lang::Type> lang::StringConstantData::resolveType(Kind           kind,
                                                                        Data const&    data,
                                                                        lang::Context& new_context)
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

lang::StringConstant::StringConstant(std::string const& prefix, std::string const& string, lang::Context& context)
    : StringConstantData(prefix, string, context)
    , LiteralConstant(StringConstantData::type_.value())
{}

std::string lang::StringConstant::toString() const
{
    return prefix_ + literal_;
}

Shared<lang::Constant> lang::StringConstant::embed(CompileContext& context) const
{
    switch (kind_)
    {
        case BYTE:
        {
            auto const& data = std::get<std::string>(data_);
            return context.exec().getByteString(data);
        }
        case CHAR:
        {
            auto const& data = std::get<std::u32string>(data_);
            return context.exec().getCodepointString(data);
        }
        case C_STRING:
        {
            auto const& data = std::get<std::string>(data_);
            return context.exec().getCString(data);
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

Shared<lang::LiteralConstant> lang::StringConstant::clone(lang::Context& new_context) const
{
    return Shared<StringConstant>(*(new StringConstant(prefix_, literal_, new_context)));
}
