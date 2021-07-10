#ifndef ANCE_SRC_ANCE_STATEMENT_DELETESTATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_DELETESTATEMENT_H_

#include "Statement.h"
#include "Expression.h"

class DeleteStatement : public Statement
{
	public:
		DeleteStatement(Expression* to_delete, bool delete_buffer, unsigned int l, unsigned int c);

		void setContainingFunction(ance::DefinedFunction* function) override;

		void build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileContext* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

	private:
		Expression* to_delete_;
		bool delete_buffer_;
};

#endif
