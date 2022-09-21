#include "UiptrConstant.h"

#include <utility>

#include "compiler/Application.h"
#include "lang/ApplicationVisitor.h"
#include "lang/type/Type.h"
#include "lang/type/UnsignedIntegerPointerType.h"
#include "validation/ValidationLogger.h"

lang::UiptrConstant::UiptrConstant(std::string value) : value_(std::move(value)) {}

std::string lang::UiptrConstant::toString() const
{
    return value_ + ":size";
}

bool lang::UiptrConstant::validate(ValidationLogger& validation_logger, lang::Location location) const
{
    if (llvm::APInt::getBitsNeeded(value_, 16) > lang::UnsignedIntegerPointerType::MINIMUM_BIT_SIZE)
    {
        validation_logger.logError("Unsigned integer pointer literals must fit into "
                                       + std::to_string(lang::UnsignedIntegerPointerType::MINIMUM_BIT_SIZE) + " bits",
                                   location);
        return false;
    }

    return true;
}

lang::ResolvingHandle<lang::Type> lang::UiptrConstant::type() const
{
    return lang::UnsignedIntegerPointerType::get();
}

llvm::Constant* lang::UiptrConstant::buildContent(llvm::Module* m)
{
    llvm::APInt size(lang::UnsignedIntegerPointerType::sizeInBits(), value_, 16);
    return llvm::ConstantInt::get(lang::UnsignedIntegerPointerType::get()->getContentType(m->getContext()), size);
}

bool lang::UiptrConstant::equals(const lang::Constant* other) const
{
    auto other_size = dynamic_cast<const UiptrConstant*>(other);
    if (!other_size) return false;

    llvm::APInt this_value(lang::UnsignedIntegerPointerType::MINIMUM_BIT_SIZE, value_, 16);
    llvm::APInt other_value(lang::UnsignedIntegerPointerType::MINIMUM_BIT_SIZE, other_size->value_, 16);

    return this_value == other_value;
}
