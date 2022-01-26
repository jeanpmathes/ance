#include "IntegerConstant.h"

#include <utility>

#include "ance/type/IntegerType.h"
#include "ance/type/Type.h"
#include "validation/ValidationLogger.h"

ance::IntegerConstant::IntegerConstant(std::string integer, int64_t size, bool is_signed, int radix)
    : text_(std::move(integer))
    , size_(size)
    , radix_(radix)
    , type_(ance::IntegerType::get(size, is_signed))
{}

bool ance::IntegerConstant::validate(ValidationLogger& validation_logger, ance::Location location)
{
    bool valid = type()->validate(validation_logger, location);
    if (!valid) return false;

    unsigned int needed_bits = llvm::APInt::getBitsNeeded(text_, radix_);

    if (needed_bits > size_)
    {
        validation_logger.logError("Integer constant too large for its type", location);
        return false;
    }

    return true;
}

ance::ResolvingHandle<ance::Type> ance::IntegerConstant::type()
{
    return type_;
}

llvm::Constant* ance::IntegerConstant::buildContent(llvm::Module* m)
{
    llvm::APInt integer(size_, text_, radix_);
    return llvm::ConstantInt::get(type_->getContentType(m->getContext()), integer);
}
