#include "BooleanConstant.h"

#include "lang/type/BooleanType.h"

lang::BooleanConstant::BooleanConstant(bool boolean) : type_(lang::BooleanType::get()), boolean_(boolean) {}

std::string lang::BooleanConstant::toString() const
{
    return boolean_ ? "true" : "false";
}

lang::ResolvingHandle<lang::Type> lang::BooleanConstant::type()
{
    return type_;
}

lang::Type const& lang::BooleanConstant::type() const
{
    return type_;
}

llvm::Constant* lang::BooleanConstant::createContent(llvm::Module* m)
{
    return boolean_ ? llvm::ConstantInt::getTrue(type_->getContentType(m->getContext()))
                    : llvm::ConstantInt::getFalse(type_->getContentType(m->getContext()));
}

bool lang::BooleanConstant::equals(lang::Constant const* other) const
{
    auto* other_boolean = dynamic_cast<BooleanConstant const*>(other);
    if (!other_boolean) return false;

    return this->boolean_ == other_boolean->boolean_;
}

Shared<lang::Constant> lang::BooleanConstant::clone() const
{
    return Shared<BooleanConstant>(*(new BooleanConstant(boolean_)));
}

Shared<lang::BooleanConstant> lang::BooleanConstant::createFalse()
{
    return Shared<lang::BooleanConstant>(*(new BooleanConstant(false)));
}

Shared<lang::BooleanConstant> lang::BooleanConstant::createTrue()
{
    return Shared<lang::BooleanConstant>(*(new BooleanConstant(true)));
}
