#ifndef ANCE_SRC_ANCE_EXPRESSION_INDEXERGET_H_
#define ANCE_SRC_ANCE_EXPRESSION_INDEXERGET_H_

#include "BuildableExpression.h"
#include "ExpressionBackedValue.h"

class IndexerGet : public BuildableExpression
{
	public:
		IndexerGet(Expression* indexed, Expression* index);

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

		~IndexerGet() override;

	private:
		Expression* indexed_;
		Expression* index_;
		ance::Value* value_{new ance::ExpressionBackedValue(this)};
};

#endif
