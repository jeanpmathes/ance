#include "SizeConstant.h"

#include <utility>

#include "SizeType.h"
#include "Application.h"

ance::SizeConstant::SizeConstant(std::string size, Application& app)
	: app_(app), type_(ance::SizeType::get()), size_(std::move(size))
{

}

ance::Type* ance::SizeConstant::getType()
{
	return type_;
}

llvm::Constant* ance::SizeConstant::buildContent(llvm::Module* m)
{
	llvm::APInt size(app_.getBitness(), size_, 10);
	return llvm::ConstantInt::get(type_->getContentType(m->getContext()), size);
}
