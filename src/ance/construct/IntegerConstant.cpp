#include "IntegerConstant.h"

#include <utility>

#include "IntegerType.h"

ance::IntegerConstant::IntegerConstant(llvm::APInt integer, bool is_signed, Application& app)
	: type_(ance::IntegerType::get(app, integer.getBitWidth(), is_signed)),
	  integer_(std::move(integer))
{
}

ance::Type* ance::IntegerConstant::getType()
{
	return type_;
}

llvm::Constant * ance::IntegerConstant::buildStored(llvm::LLVMContext& c)
{
	return llvm::ConstantInt::get(type_->getNativeType(c), integer_);
}
