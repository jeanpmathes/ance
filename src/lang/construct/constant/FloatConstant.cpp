#include "FloatConstant.h"

#include "lang/type/Type.h"

lang::FloatConstant::FloatConstant(std::string                       number,
                                   const llvm::fltSemantics&         semantics,
                                   lang::ResolvingHandle<lang::Type> type)
    : type_(type)
    , float_(semantics, number)
{}

lang::ResolvingHandle<lang::Type> lang::FloatConstant::type()
{
    return type_;
}

llvm::Constant* lang::FloatConstant::buildContent(llvm::Module* m)
{
    return llvm::ConstantFP::get(type_->getContentType(m->getContext()), float_);
}
