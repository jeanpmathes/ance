#include "FixedWidthIntegerType.h"

#include "compiler/Application.h"
#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/PredefinedFunction.h"
#include "lang/construct/value/WrappedNativeValue.h"
#include "lang/scope/GlobalScope.h"
#include "lang/type/BooleanType.h"
#include "lang/type/SizeType.h"
#include "validation/ValidationLogger.h"

lang::FixedWidthIntegerType::FixedWidthIntegerType(uint64_t bit_size, bool is_signed)
    : TypeDefinition(lang::Identifier::from((is_signed ? "i" : "ui") + std::to_string(bit_size)))
    , bit_size_(bit_size)
    , is_signed_(is_signed)
{}

const lang::FixedWidthIntegerType* lang::FixedWidthIntegerType::isFixedWidthIntegerType() const
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

std::string lang::FixedWidthIntegerType::createMangledName() const
{
    return std::string(name().text());
}

lang::TypeRegistry<std::pair<uint64_t, bool>>& lang::FixedWidthIntegerType::getIntegerTypes()
{
    static TypeRegistry<std::pair<uint64_t, bool>> integer_types;
    return integer_types;
}

lang::TypeDefinitionRegistry* lang::FixedWidthIntegerType::getRegistry()
{
    return &getIntegerTypes();
}

lang::ResolvingHandle<lang::Type> lang::FixedWidthIntegerType::get(uint64_t bit_size, bool is_signed)
{
    std::vector<lang::ResolvingHandle<lang::Type>> used_types;

    std::optional<lang::ResolvingHandle<lang::Type>> defined_type =
        getIntegerTypes().get(used_types, std::make_pair(bit_size, is_signed));

    if (defined_type.has_value()) { return defined_type.value(); }
    else
    {
        auto*                             integer_type = new lang::FixedWidthIntegerType(bit_size, is_signed);
        lang::ResolvingHandle<lang::Type> type =
            lang::makeHandled<lang::Type>(std::unique_ptr<lang::FixedWidthIntegerType>(integer_type));
        getIntegerTypes().add(std::move(used_types), std::make_pair(bit_size, is_signed), type);

        return type;
    }
}

std::optional<size_t> lang::FixedWidthIntegerType::getBitSize() const
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