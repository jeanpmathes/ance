#include "BooleanConstant.h"

#include "lang/type/IntegerType.h"

lang::BooleanConstant::BooleanConstant(bool boolean) : type_(lang::IntegerType::getBooleanType()), boolean_(boolean) {}

std::string lang::BooleanConstant::toString() const
{
    return boolean_ ? "true" : "false";
}

lang::ResolvingHandle<lang::Type> lang::BooleanConstant::type()
{
    return type_;
}

llvm::Constant* lang::BooleanConstant::buildContent(llvm::Module* m)
{
    return boolean_ ? llvm::ConstantInt::getTrue(type_->getContentType(m->getContext()))
                    : llvm::ConstantInt::getFalse(type_->getContentType(m->getContext()));
}

std::shared_ptr<lang::BooleanConstant> lang::BooleanConstant::createFalse()
{
    return std::shared_ptr<lang::BooleanConstant>(new BooleanConstant(false));
}

std::shared_ptr<lang::BooleanConstant> lang::BooleanConstant::createTrue()
{
    return std::shared_ptr<lang::BooleanConstant>(new BooleanConstant(true));
}
