#include "IntegerConstant.h"

#include <utility>

#include "IntegerType.h"

ance::IntegerConstant::IntegerConstant(llvm::APInt integer, bool is_signed, ance::Scope* scope)
	: type_(ance::IntegerType::get(scope, integer.getBitWidth(), is_signed)),
	  integer_(std::move(integer))
{
}

ance::Type* ance::IntegerConstant::getType()
{
	return type_;
}

llvm::Constant* ance::IntegerConstant::getConstant(llvm::LLVMContext& c)
{
	if (!constant_)
	{
		constant_ = llvm::ConstantInt::get(type_->getNativeType(c), integer_);
	}

	return constant_;
}
