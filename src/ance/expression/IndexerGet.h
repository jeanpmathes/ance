#ifndef ANCE_SRC_ANCE_EXPRESSION_INDEXERGET_H_
#define ANCE_SRC_ANCE_EXPRESSION_INDEXERGET_H_

#include "DelayableExpression.h"
#include "ExpressionBackedValue.h"

class IndexerGet : public DelayableExpression
{
	public:
		IndexerGet(Expression* indexed, Expression* index);

		void setScope(ance::Scope* scope) override;

		ance::Type* getType() override;

		void buildValue(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileContext* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		~IndexerGet() override;

	private:
		Expression* indexed_;
		Expression* index_;
};

#endif
