#include "IntegerConstant.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/Context.h"
#include "lang/type/FixedWidthIntegerType.h"
#include "lang/type/IntegerType.h"
#include "lang/type/Type.h"
#include "validation/ValidationLogger.h"

lang::IntegerConstant::IntegerConstant(std::string integer, uint8_t radix, lang::ResolvingHandle<lang::Type> type)
    : text_(std::move(integer))
    , radix_(radix)
    , type_(type)
    , integer_type_(type->isIntegerType())
{
    text_.erase(0, std::min(text_.find_first_not_of('0'), text_.size() - 1));
}

lang::IntegerConstant::IntegerConstant(std::string const& integer, bool is_signed, lang::Context& new_context)
    : IntegerConstant(integer,
                      10,
                      new_context.getFixedWidthIntegerType(llvm::APInt::getBitsNeeded(integer, 10), is_signed))
{}

std::string lang::IntegerConstant::toString() const
{
    std::string prefix;

    switch (radix_)
    {
        case 2:
            prefix = "0b";
            break;
        case 8:
            prefix = "0o";
            break;
        case 10:
            prefix = "";
            break;
        case 16:
            prefix = "0x";
            break;
        default:
            throw std::logic_error("Invalid radix");
    }

    return prefix + text_ + ":" + integer_type_->getSuffix();
}

bool lang::IntegerConstant::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    bool const valid = type().validate(validation_logger, location);
    if (!valid) return false;

    unsigned int needed_bits = llvm::APInt::getBitsNeeded(text_, radix_);

    if (radix_ == 2 || radix_ == 8 || radix_ == 16)
    {
        // Code from llvm::APInt::getBitsNeeded
        // Required as the required size can be larger than needed

        auto get_needed_bits_corrected = [&] {
            unsigned const    is_negative = text_[0] == '-';
            llvm::APInt const tmp(needed_bits, text_, radix_);

            unsigned const log = tmp.logBase2();
            if (log == static_cast<unsigned>(-1)) { return is_negative + 1; }
            else if (is_negative && tmp.isPowerOf2()) { return is_negative + log; }
            else { return is_negative + log + 1; }
        };

        needed_bits = get_needed_bits_corrected();
    }

    auto bit_size = integer_type_->getBitSize();

    if (bit_size.hasValue())
    {
        if (needed_bits > bit_size.value())
        {
            validation_logger.logError("Integer literal larger than the fixed " + std::to_string(bit_size.value())
                                           + " bit size",
                                       location);
            return false;
        }
    }
    else
    {
        size_t const min_bit_size = integer_type_->getMinimumBitSize();

        if (needed_bits > min_bit_size)
        {
            validation_logger.logError("Integer literal larger than minimum ensured " + std::to_string(min_bit_size)
                                           + " bits",
                                       location);
            return false;
        }
    }

    return true;
}

lang::ResolvingHandle<lang::Type> lang::IntegerConstant::type()
{
    return type_;
}

lang::Type const& lang::IntegerConstant::type() const
{
    return type_;
}

llvm::Constant* lang::IntegerConstant::createContent(CompileContext& context)
{
    llvm::APInt const integer(static_cast<unsigned int>(integer_type_->getNativeBitSize()), text_, radix_);
    return context.exec().getIntegerConstant(integer);
}

bool lang::IntegerConstant::equals(lang::Constant const* other) const
{
    auto other_int = dynamic_cast<IntegerConstant const*>(other);
    if (!other_int) return false;

    if (other_int->integer_type_ != integer_type_) return false;

    llvm::APInt const this_value(
        static_cast<unsigned int>(integer_type_->getBitSize().valueOr(integer_type_->getMinimumBitSize())),
        text_,
        radix_);
    llvm::APInt const other_value(static_cast<unsigned int>(other_int->integer_type_->getBitSize().valueOr(
                                      other_int->integer_type_->getMinimumBitSize())),
                                  other_int->text_,
                                  other_int->radix_);

    if (this_value.getBitWidth() != other_value.getBitWidth()) return false;

    return this_value == other_value;
}

Shared<lang::Constant> lang::IntegerConstant::clone(lang::Context& new_context) const
{
    return Shared<Constant>(*(new IntegerConstant(text_, radix_, type_->getUndefinedTypeClone(new_context))));
}
