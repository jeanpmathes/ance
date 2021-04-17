#ifndef ANCE_SRC_ANCE_EXPRESSION_VARIABLEEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_VARIABLEEXPRESSION_H_

#include "BuildableExpression.h"

namespace ance {
	class Variable;
	class Scope;
}

class VariableExpression : public BuildableExpression
{
public:
	explicit VariableExpression(ance::Variable* variable);

	ance::Type* getType() override;

	ance::Value* getValue() override;
	llvm::Value* build(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;

	~VariableExpression() override;

private:
	ance::Variable* variable_;
	ance::Value* value_;
};
#endif