#include "DefaultValueExpression.h"

#include "Value.h"
#include "Constant.h"
#include "Type.h"

#include "ExpressionBackedConstant.h"

DefaultValueExpression::DefaultValueExpression(ance::Type* type) : type_(type), constant_(new ance::ExpressionBackedConstant(this))
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

llvm::Value* DefaultValueExpression::build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return buildConstant(c);
}

ance::Constant* DefaultValueExpression::getConstantValue()
{
	return constant_;
}

llvm::Constant* DefaultValueExpression::buildConstant(llvm::LLVMContext& c)
{
	return type_->getDefault(c);
}

DefaultValueExpression::~DefaultValueExpression() = default;