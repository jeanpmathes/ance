#ifndef ANCE_SRC_ANCE_EXPRESSION_ALLOCATIONEXPRESSION_H_
#define ANCE_SRC_ANCE_EXPRESSION_ALLOCATIONEXPRESSION_H_

#include "BuildableExpression.h"
#include "Runtime.h"
#include "Application.h"

class AllocationExpression : public BuildableExpression
{
	public:
		AllocationExpression(Runtime::Allocator allocation, ance::Type* type, Application& app);

		ance::Type* getType() override;

		ance::Value* getValue() override;

		llvm::Value* build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		~AllocationExpression() override;

	private:
		Runtime::Allocator allocation_;
		ance::Type* allocated_type_;
		ance::Type* return_type_;
		ance::Value* value_;
};

#endif
