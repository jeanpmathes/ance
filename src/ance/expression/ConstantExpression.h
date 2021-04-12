#ifndef CONSTANT_EXPRESSION_H
#define CONSTANT_EXPRESSION_H

#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Constant.h"

#include "Expression.h"

namespace ance
{
	class Constant;
}

class ConstantExpression : public virtual Expression
{
public:
	virtual ance::Constant* get_constant_value() = 0;
};
#endif