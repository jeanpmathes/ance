#include "FloatConstant.h"

#include <utility>

#include "lang/type/Type.h"

lang::FloatConstant::FloatConstant(std::string const&                number,
                                   llvm::fltSemantics const&         semantics,
                                   lang::ResolvingHandle<lang::Type> type)
    : text_(number)
    , type_(std::move(type))
    , float_(semantics, number)
{}

std::string lang::FloatConstant::toString() const
{
    std::string suffix;

    if (type_->isFloatingPointType(16)) suffix += "h";
    if (type_->isFloatingPointType(32)) suffix += "s";
    if (type_->isFloatingPointType(64)) suffix += "d";
    if (type_->isFloatingPointType(128)) suffix += "q";

    return text_ + suffix;
}

lang::ResolvingHandle<lang::Type> lang::FloatConstant::type()
{
    return type_;
}

lang::Type const& lang::FloatConstant::type() const
{
    return type_;
}

llvm::Constant* lang::FloatConstant::createContent(llvm::Module& m)
{
    return llvm::ConstantFP::get(type_->getContentType(m.getContext()), float_);
}

bool lang::FloatConstant::equals(lang::Constant const* other) const
{
    auto other_float = dynamic_cast<FloatConstant const*>(other);
    if (!other_float) return false;

    return this->float_ == other_float->float_;
}

Shared<lang::Constant> lang::FloatConstant::clone() const
{
    return Shared<lang::Constant>(*(new FloatConstant(text_, float_.getSemantics(), type_->createUndefinedClone())));
}
