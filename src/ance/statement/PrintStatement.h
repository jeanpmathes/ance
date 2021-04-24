#include "Statement.h"

class Expression;

class PrintStatement : public Statement
{
	public:
		PrintStatement(ance::Function* function, unsigned int l, unsigned int c, Expression* expression);

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
