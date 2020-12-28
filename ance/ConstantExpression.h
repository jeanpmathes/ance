#ifndef CONSTANT_EXPRESSION_H
#define CONSTANT_EXPRESSION_H

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Constant.h"

#include "Expression.h"

namespace ance
{
	class Constant;
}

class ConstantExpression : public Expression
{
public:
	virtual ance::Constant* get_constant_value() = 0;
	virtual llvm::Constant* build_constant(llvm::LLVMContext& c) = 0;
};
#endif