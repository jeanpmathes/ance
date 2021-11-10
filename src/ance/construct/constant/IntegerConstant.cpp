#include "IntegerConstant.h"

#include <utility>

#include "ance/type/IntegerType.h"
#include "ance/type/Type.h"

ance::IntegerConstant::IntegerConstant(llvm::APInt integer, bool is_signed)
    : type_(ance::IntegerType::get(integer.getBitWidth(), is_signed))
    , integer_(std::move(integer))
{}

ance::ResolvingHandle<ance::Type> ance::IntegerConstant::type()
{
    return type_;
}

llvm::Constant* ance::IntegerConstant::buildContent(llvm::Module* m)
{
    return llvm::ConstantInt::get(type_->getContentType(m->getContext()), integer_);
}
