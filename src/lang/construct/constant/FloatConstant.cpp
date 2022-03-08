#include "FloatConstant.h"

#include "lang/type/Type.h"

lang::FloatConstant::FloatConstant(std::string                       number,
                                   const llvm::fltSemantics&         semantics,
                                   lang::ResolvingHandle<lang::Type> type)
    : text_(number)
    , type_(type)
    , float_(semantics, number)
{}

std::string lang::FloatConstant::toString() const
{
    std::string suffix;

    if (type_->isFloatingPointType(16)) suffix += "h";
    if (type_->isFloatingPointType(32)) suffix += "f";
    if (type_->isFloatingPointType(64)) suffix += "d";
    if (type_->isFloatingPointType(128)) suffix += "q";

    return text_ + suffix;
}

lang::ResolvingHandle<lang::Type> lang::FloatConstant::type()
{
    return type_;
}

llvm::Constant* lang::FloatConstant::buildContent(llvm::Module* m)
{
    return llvm::ConstantFP::get(type_->getContentType(m->getContext()), float_);
}