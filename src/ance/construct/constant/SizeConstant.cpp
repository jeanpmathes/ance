#include "SizeConstant.h"

#include <utility>

#include "ance/type/SizeType.h"
#include "ance/type/Type.h"
#include "compiler/Application.h"
#include "validation/ValidationLogger.h"

ance::SizeConstant::SizeConstant(std::string value) : type_(ance::SizeType::getSize()), value_(std::move(value)) {}

bool ance::SizeConstant::validate(ValidationLogger& validation_logger, ance::Location location)
{
    if (llvm::APInt::getBitsNeeded(value_, 10) > ance::SizeType::MINIMUM_BIT_SIZE)
    {
        validation_logger.logError("Size literals must fit into " + std::to_string(ance::SizeType::MINIMUM_BIT_SIZE)
                                       + " bits",
                                   location);
        return false;
    }

    return true;
}

ance::ResolvingHandle<ance::Type> ance::SizeConstant::type()
{
    return type_;
}

llvm::Constant* ance::SizeConstant::buildContent(llvm::Module* m)
{
    llvm::APInt size(ance::SizeType::getSizeWidth(), value_, 10);
    return llvm::ConstantInt::get(type_->getContentType(m->getContext()), size);
}
