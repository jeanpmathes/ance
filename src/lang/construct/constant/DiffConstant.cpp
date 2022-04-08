#include "DiffConstant.h"

#include <utility>

#include "lang/type/SizeType.h"
#include "compiler/Application.h"
#include "validation/ValidationLogger.h"

lang::DiffConstant::DiffConstant(std::string value) : type_(lang::SizeType::getDiff()), value_(std::move(value)) {}

std::string lang::DiffConstant::toString() const
{
    return value_ + ":diff";
}

bool lang::DiffConstant::validate(ValidationLogger& validation_logger, lang::Location location)
{
    if (llvm::APInt::getBitsNeeded(value_, 10) > lang::SizeType::MINIMUM_BIT_SIZE)
    {
        validation_logger.logError("Diff literals must fit into " + std::to_string(lang::SizeType::MINIMUM_BIT_SIZE)
                                       + " bits",
                                   location);
        return false;
    }

    return true;
}

lang::ResolvingHandle<lang::Type> lang::DiffConstant::type()
{
    return type_;
}

llvm::Constant* lang::DiffConstant::buildContent(llvm::Module* m)
{
    llvm::APInt size(lang::SizeType::getDiffWidth(), value_, 10);
    return llvm::ConstantInt::get(type_->getContentType(m->getContext()), size);
}

bool lang::DiffConstant::equals(const lang::Constant* other) const
{
    auto other_diff = dynamic_cast<const DiffConstant*>(other);
    if (!other_diff) return false;

    llvm::APInt this_value(lang::SizeType::MINIMUM_BIT_SIZE, value_, 10);
    llvm::APInt other_value(lang::SizeType::MINIMUM_BIT_SIZE, other_diff->value_, 10);

    return this_value == other_value;
}
