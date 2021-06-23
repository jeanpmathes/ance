#include "Statement.h"

class Expression;

class PrintStatement : public Statement
{
	public:
		PrintStatement(Expression* str, Expression* len, unsigned int l, unsigned int c);

		void setContainingFunction(ance::DefinedFunction* function) override;

		void build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

	private:
		Expression* str_;
		Expression* len_;
};
