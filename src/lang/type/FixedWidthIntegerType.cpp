#include "FixedWidthIntegerType.h"

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "compiler/RoughlyCastedValue.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/CharType.h"
#include "validation/ValidationLogger.h"

lang::FixedWidthIntegerType::FixedWidthIntegerType(uint64_t bit_size, bool is_signed)
    : TypeDefinition(lang::Identifier::like((is_signed ? "i" : "u") + std::to_string(bit_size)))
    , bit_size_(bit_size)
    , is_signed_(is_signed)
{}

lang::FixedWidthIntegerType const* lang::FixedWidthIntegerType::isFixedWidthIntegerType() const
{
    return this;
}

bool lang::FixedWidthIntegerType::isFixedWidthIntegerType(uint64_t bit_size, bool is_signed) const
{
    return (bit_size_ == bit_size) && (is_signed_ == is_signed);
}

bool lang::FixedWidthIntegerType::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    if (bit_size_ == 0)
    {
        validation_logger.logError("Integer type size must be positive", location);
        return false;
    }

    if (bit_size_ > MAX_INTEGER_SIZE)
    {
        validation_logger.logError("Integer type size cannot be larger than " + std::to_string(MAX_INTEGER_SIZE),
                                   location);
        return false;
    }

    return true;
}

bool lang::FixedWidthIntegerType::isCastingPossibleTo(lang::Type const& other) const
{
    if (other.isCharType() && bit_size_ == lang::CharType::SIZE_IN_BITS && !is_signed_) return true;
    if (other.isFloatingPointType()) return true;

    return IntegerType::isCastingPossibleTo(other);
}

bool lang::FixedWidthIntegerType::validateCast(lang::Type const& other,
                                               lang::Location    location,
                                               ValidationLogger& validation_logger) const
{
    return IntegerType::validateCast(other, location, validation_logger);
}

Shared<lang::Value> lang::FixedWidthIntegerType::buildCast(lang::Type const& other,
                                                           Shared<lang::Value>               value,
                                                           CompileContext&                   context) const
{
    if (other.isCharType() && bit_size_ == lang::CharType::SIZE_IN_BITS && !is_signed_)
    {
        return context.exec().performIntegerReinterpretation(value, other);
    }

    if (other.isXOrVectorOfX([](auto& t) { return t.isFloatingPointType(); }))
    {
        return context.exec().computeConversionI2FP(value, other);
    }

    return IntegerType::buildCast(other, value, context);
}

std::string lang::FixedWidthIntegerType::createMangledName() const
{
    return std::string(name().text());
}

Optional<size_t> lang::FixedWidthIntegerType::getBitSize() const
{
    return bit_size_;
}

size_t lang::FixedWidthIntegerType::getNativeBitSize() const
{
    return bit_size_;
}

bool lang::FixedWidthIntegerType::isSigned() const
{
    return is_signed_;
}

size_t lang::FixedWidthIntegerType::getMinimumBitSize() const
{
    return bit_size_;
}

std::string lang::FixedWidthIntegerType::getSuffix() const
{
    return std::to_string(bit_size_);
}

lang::ResolvingHandle<lang::Type> lang::FixedWidthIntegerType::clone(lang::Context& new_context) const
{
    return new_context.getFixedWidthIntegerType(bit_size_, is_signed_);
}
