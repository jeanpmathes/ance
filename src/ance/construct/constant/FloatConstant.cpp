#include "FloatConstant.h"

#include "ance/type/Type.h"

ance::FloatConstant::FloatConstant(std::string                       number,
                                   const llvm::fltSemantics&         semantics,
                                   ance::ResolvingHandle<ance::Type> type)
    : type_(type)
    , float_(semantics, number)
{}

ance::ResolvingHandle<ance::Type> ance::FloatConstant::type()
{
    return type_;
}

llvm::Constant* ance::FloatConstant::buildContent(llvm::Module* m)
{
    return llvm::ConstantFP::get(type_->getContentType(m->getContext()), float_);
}
