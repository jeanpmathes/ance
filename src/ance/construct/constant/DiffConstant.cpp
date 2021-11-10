#include "DiffConstant.h"

#include <utility>

#include "ance/type/SizeType.h"
#include "ance/type/Type.h"
#include "compiler/Application.h"

ance::DiffConstant::DiffConstant(std::string value) : type_(ance::SizeType::getDiff()), value_(std::move(value)) {}

ance::ResolvingHandle<ance::Type> ance::DiffConstant::type()
{
    return type_;
}

llvm::Constant* ance::DiffConstant::buildContent(llvm::Module* m)
{
    llvm::APInt size(ance::SizeType::getDiffWidth(), value_, 10);
    return llvm::ConstantInt::get(type_->getContentType(m->getContext()), size);
}
