#include "BooleanConstant.h"

#include "lang/type/BooleanType.h"

lang::BooleanConstant::BooleanConstant(bool boolean) : type_(lang::BooleanType::get()), boolean_(boolean) {}

std::string lang::BooleanConstant::toString() const
{
    return boolean_ ? "true" : "false";
}

lang::ResolvingHandle<lang::Type> lang::BooleanConstant::type() const
{
    return type_;
}

llvm::Constant* lang::BooleanConstant::buildContent(llvm::Module* m)
{
    return boolean_ ? llvm::ConstantInt::getTrue(type_->getContentType(m->getContext()))
                    : llvm::ConstantInt::getFalse(type_->getContentType(m->getContext()));
}

bool lang::BooleanConstant::equals(const lang::Constant* other) const
{
    auto* other_boolean = dynamic_cast<const BooleanConstant*>(other);
    if (!other_boolean) return false;

    return this->boolean_ == other_boolean->boolean_;
}

std::shared_ptr<lang::BooleanConstant> lang::BooleanConstant::createFalse()
{
    return std::shared_ptr<lang::BooleanConstant>(new BooleanConstant(false));
}

std::shared_ptr<lang::BooleanConstant> lang::BooleanConstant::createTrue()
{
    return std::shared_ptr<lang::BooleanConstant>(new BooleanConstant(true));
}
