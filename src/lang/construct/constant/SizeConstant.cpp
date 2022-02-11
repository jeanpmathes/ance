#include "SizeConstant.h"

#include <utility>

#include "lang/type/SizeType.h"
#include "lang/type/Type.h"
#include "compiler/Application.h"
#include "validation/ValidationLogger.h"

lang::SizeConstant::SizeConstant(std::string value) : type_(lang::SizeType::getSize()), value_(std::move(value)) {}

bool lang::SizeConstant::validate(ValidationLogger& validation_logger, lang::Location location)
{
    if (llvm::APInt::getBitsNeeded(value_, 10) > lang::SizeType::MINIMUM_BIT_SIZE)
    {
        validation_logger.logError("Size literals must fit into " + std::to_string(lang::SizeType::MINIMUM_BIT_SIZE)
                                       + " bits",
                                   location);
        return false;
    }

    return true;
}

lang::ResolvingHandle<lang::Type> lang::SizeConstant::type()
{
    return type_;
}

llvm::Constant* lang::SizeConstant::buildContent(llvm::Module* m)
{
    llvm::APInt size(lang::SizeType::getSizeWidth(), value_, 10);
    return llvm::ConstantInt::get(type_->getContentType(m->getContext()), size);
}
