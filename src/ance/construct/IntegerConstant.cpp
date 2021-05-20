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

void ance::IntegerConstant::build(llvm::LLVMContext& c)
{
	assert(!constant_);
	constant_ = llvm::ConstantInt::get(type_->getNativeType(c), integer_);
}

llvm::Constant * ance::IntegerConstant::getNativeConstant()
{
	assert(constant_);
	return constant_;
}
