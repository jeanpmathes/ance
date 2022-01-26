#include "DiffConstant.h"

#include <utility>

#include "ance/type/SizeType.h"
#include "compiler/Application.h"
#include "validation/ValidationLogger.h"

ance::DiffConstant::DiffConstant(std::string value) : type_(ance::SizeType::getDiff()), value_(std::move(value)) {}

bool ance::DiffConstant::validate(ValidationLogger& validation_logger, ance::Location location)
{
    if (llvm::APInt::getBitsNeeded(value_, 10) > ance::SizeType::MINIMUM_BIT_SIZE)
    {
        validation_logger.logError("Diff literals must fit into " + std::to_string(ance::SizeType::MINIMUM_BIT_SIZE)
                                       + " bits",
                                   location);
        return false;
    }

    return true;
}

ance::ResolvingHandle<ance::Type> ance::DiffConstant::type()
{
    return type_;
}

llvm::Constant* ance::DiffConstant::buildContent(llvm::Module* m)
{
    llvm::APInt size(ance::SizeType::getDiffWidth(), value_, 10);
    return llvm::ConstantInt::get(type_->getContentType(m->getContext()), size);
}
