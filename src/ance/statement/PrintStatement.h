#include "Statement.h"

class Expression;

class PrintStatement : public Statement
{
	public:
		PrintStatement(Expression* expression, unsigned int l, unsigned int c);

		void setContainingFunction(ance::Function* function) override;

		void build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) override;

		~PrintStatement() override;

	private:
		Expression* expression_;
};
