#include "IntegerConstant.h"

#include <utility>

#include "lang/type/IntegerType.h"
#include "lang/type/Type.h"
#include "validation/ValidationLogger.h"

lang::IntegerConstant::IntegerConstant(std::string integer, int64_t size, bool is_signed, int radix)
    : text_(std::move(integer))
    , size_(size)
    , radix_(radix)
    , type_(lang::IntegerType::get(size, is_signed))
{
    text_.erase(0, std::min(text_.find_first_not_of('0'), text_.size() - 1));
}

lang::IntegerConstant::IntegerConstant(const std::string& integer, bool is_signed)
    : IntegerConstant(integer, llvm::APInt::getBitsNeeded(integer, 10), is_signed, 10)
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
            throw std::runtime_error("Invalid radix");
    }

    return prefix + text_ + ":" + std::to_string(size_);
}

bool lang::IntegerConstant::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    bool valid = type()->validate(validation_logger, location);
    if (!valid) return false;

    unsigned int needed_bits = llvm::APInt::getBitsNeeded(text_, radix_);

    if (radix_ == 2 || radix_ == 8 || radix_ == 16)
    {
        // Code from llvm::APInt::getBitsNeeded
        // Required as the required size can be larger than needed

        unsigned    is_negative = text_[0] == '-';
        llvm::APInt tmp(needed_bits, text_, radix_);

        unsigned log = tmp.logBase2();
        if (log == (unsigned) -1) { return is_negative + 1; }
        else if (is_negative && tmp.isPowerOf2()) {
            return is_negative + log;
        }
        else {
            return is_negative + log + 1;
        }
    }

    if (needed_bits > size_)
    {
        validation_logger.logError("Integer constant too large for its type", location);
        return false;
    }

    return true;
}

lang::ResolvingHandle<lang::Type> lang::IntegerConstant::type() const
{
    return type_;
}

llvm::Constant* lang::IntegerConstant::buildContent(llvm::Module* m)
{
    llvm::APInt integer(size_, text_, radix_);
    return llvm::ConstantInt::get(type_->getContentType(m->getContext()), integer);
}

bool lang::IntegerConstant::equals(const lang::Constant* other) const
{
    auto other_int = dynamic_cast<const IntegerConstant*>(other);
    if (!other_int) return false;

    llvm::APInt this_value(size_, text_, radix_);
    llvm::APInt other_value(other_int->size_, other_int->text_, other_int->radix_);

    if (this_value.getBitWidth() != other_value.getBitWidth()) return false;

    return this_value == other_value;
}
