#ifndef ANCE_EXPRESSIONVALUE_H
#define ANCE_EXPRESSIONVALUE_H

#include "Value.h"

namespace ance
{
	class ExpressionValue : public Value
	{
	public:
		ExpressionValue(Expression* expression);
		ance::Type* get_type() override;
		llvm::Value* get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;

	private:
		Expression* expression_;
	};
}
#endif