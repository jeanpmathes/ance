#include "SizeConstant.h"

#include <utility>

#include "ance/type/SizeType.h"
#include "compiler/Application.h"

ance::SizeConstant::SizeConstant(std::string size, Application& app)
    : app_(app)
    , type_(ance::SizeType::getSize())
    , size_(std::move(size))
{}

ance::Type* ance::SizeConstant::type()
{
    return type_;
}

llvm::Constant* ance::SizeConstant::buildContent(llvm::Module* m)
{
    llvm::APInt size(app_.getBitness(), size_, 10);
    return llvm::ConstantInt::get(type_->getContentType(m->getContext()), size);
}
