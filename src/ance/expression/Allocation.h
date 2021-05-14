#ifndef ANCE_SRC_ANCE_EXPRESSION_ALLOCATION_H_
#define ANCE_SRC_ANCE_EXPRESSION_ALLOCATION_H_

#include "BuildableExpression.h"
#include "Runtime.h"
#include "Application.h"

class Allocation : public BuildableExpression
{
	public:
		Allocation(Runtime::Allocator allocation, ance::Type* type, Expression* count, Application& app);

		void setScope(ance::Scope* scope) override;

		ance::Type* getType() override;

		ance::Value* getValue() override;

		llvm::Value* build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		~Allocation() override;

	private:
		Runtime::Allocator allocation_;
		ance::Type* allocated_type_;
		Expression* count_;
		ance::Type* return_type_;
		ance::Value* value_;
};

#endif
