#include "DefaultValueExpression.h"

#include "Value.h"
#include "Constant.h"
#include "Type.h"

DefaultValueExpression::DefaultValueExpression(ance::Type* type)
	: type_(type)
{
}

ance::Type* DefaultValueExpression::getType()
{
	return type_;
}

ance::Value* DefaultValueExpression::getValue()
{
	return constant_;
}

ance::Constant* DefaultValueExpression::getConstantValue()
{
	return constant_;
}

llvm::Constant* DefaultValueExpression::buildContentConstant(llvm::LLVMContext& c)
{
	return type_->getDefaultContent(c);
}

DefaultValueExpression::~DefaultValueExpression() = default;