#ifndef ANCE_CONSTANT_H
#define ANCE_CONSTANT_H

#include "ConstantExpression.h"

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

class ConstantExpression;

namespace ance
{
	class Constant
	{
	public:
		Constant(ConstantExpression* expression);
		llvm::Constant* get_constant(llvm::LLVMContext& c);

	private:
		ConstantExpression* expression_;
	};
}
#endif