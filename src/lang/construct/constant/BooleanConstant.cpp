#include "BooleanConstant.h"

#include "lang/ApplicationVisitor.h"
#include "lang/Context.h"
#include "lang/type/BooleanType.h"

lang::BooleanConstant::BooleanConstant(bool boolean, lang::Context& context)
    : type_(context.getBooleanType())
    , boolean_(boolean)
{}

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

llvm::Constant* lang::BooleanConstant::createContent(llvm::Module& m)
{
    return boolean_ ? llvm::ConstantInt::getTrue(type_->getContentType(m.getContext()))
                    : llvm::ConstantInt::getFalse(type_->getContentType(m.getContext()));
}

bool lang::BooleanConstant::equals(lang::Constant const* other) const
{
    auto* other_boolean = dynamic_cast<BooleanConstant const*>(other);
    if (!other_boolean) return false;

    return this->boolean_ == other_boolean->boolean_;
}

Shared<lang::Constant> lang::BooleanConstant::clone(lang::Context& new_context) const
{
    return Shared<BooleanConstant>(*(new BooleanConstant(boolean_, new_context)));
}

Shared<lang::BooleanConstant> lang::BooleanConstant::createFalse(lang::Context& new_context)
{
    return Shared<lang::BooleanConstant>(*(new BooleanConstant(false, new_context)));
}

Shared<lang::BooleanConstant> lang::BooleanConstant::createTrue(lang::Context& new_context)
{
    return Shared<lang::BooleanConstant>(*(new BooleanConstant(true, new_context)));
}
