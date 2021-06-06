#ifndef ANCE_SRC_ANCE_ASSIGNABLE_INDEXERSET_H_
#define ANCE_SRC_ANCE_ASSIGNABLE_INDEXERSET_H_

#include "Assignable.h"

#include "Expression.h"
#include "AssignableExpression.h"

class IndexerSet : public Assignable
{
	public:
		explicit IndexerSet(AssignableExpression* indexed, Expression* index);

		void setScope(ance::Scope* scope) override;

		void assign(
			ance::Value* value,
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

	private:
		AssignableExpression* indexed_;
		Expression* index_;
};

#endif
