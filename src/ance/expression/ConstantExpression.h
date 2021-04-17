#ifndef ANCE_SRC_ANCE_EXPRESSION_CONSTANTEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_CONSTANTEXPRESSION_H_

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
	virtual ance::Constant* getConstantValue() = 0;
	ance::Value * getValue() override;
};
#endif