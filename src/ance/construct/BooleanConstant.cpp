#include "BooleanConstant.h"

#include <llvm/IR/Constant.h>

#include "IntegerType.h"

ance::BooleanConstant::BooleanConstant(bool boolean, Application& app)
	: type_(ance::IntegerType::get(app, 1, true)), boolean_(boolean)
{

}

ance::Type* ance::BooleanConstant::getType()
{
	return type_;
}

llvm::Constant* ance::BooleanConstant::getConstant(llvm::LLVMContext& c)
{
	if (!constant_)
	{
		constant_ = boolean_ ? llvm::ConstantInt::getTrue(type_->getNativeType(c))
							 : llvm::ConstantInt::getFalse(type_->getNativeType(c));
	}

	return constant_;
}

ance::BooleanConstant* ance::BooleanConstant::createFalse(Application& app)
{
	return new BooleanConstant(false, app);
}

ance::BooleanConstant* ance::BooleanConstant::createTrue(Application& app)
{
	return new BooleanConstant(true, app);
}
