#include "SizeConstant.h"

#include <utility>

#include "ance/type/SizeType.h"
#include "ance/type/Type.h"
#include "compiler/Application.h"

ance::SizeConstant::SizeConstant(std::string value) : type_(ance::SizeType::getSize()), value_(std::move(value)) {}

ance::ResolvingHandle<ance::Type> ance::SizeConstant::type()
{
    return type_;
}

llvm::Constant* ance::SizeConstant::buildContent(llvm::Module* m)
{
    llvm::APInt size(ance::SizeType::getSizeWidth(), value_, 10);
    return llvm::ConstantInt::get(type_->getContentType(m->getContext()), size);
}
