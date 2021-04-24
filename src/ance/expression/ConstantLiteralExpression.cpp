#include "ConstantLiteralExpression.h"

#include "Constant.h"
#include "Scope.h"

ConstantLiteralExpression::ConstantLiteralExpression(ance::Constant* constant)
	: constant_(constant)
{

}

ance::Type* ConstantLiteralExpression::getType()
{
	return constant_->getType();
}

ance::Constant* ConstantLiteralExpression::getConstantValue()
{
	return constant_;
}
