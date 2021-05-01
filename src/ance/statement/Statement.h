#ifndef ANCE_SRC_ANCE_STATEMENT_STATEMENT_H_
#define ANCE_SRC_ANCE_STATEMENT_STATEMENT_H_

#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/DIBuilder.h"

#include "CompileState.h"

class CompileState;

namespace ance
{
class Function;
}

class Statement
{
	public:
		Statement(unsigned int l, unsigned int c);

		virtual void setContainingFunction(ance::Function* function);

		[[nodiscard]] ance::Function* getContainingFunction() const;

		[[nodiscard]] unsigned int getLine() const;

		[[nodiscard]] unsigned int getColumn() const;

		virtual void build(
			llvm::LLVMContext& c,
			llvm::Module* m,
			CompileState* state,
			llvm::IRBuilder<>& ir,
			llvm::DIBuilder* di
		) = 0;

		virtual ~Statement() = 0;

	private:
		ance::Function* function_{nullptr};
		unsigned int line_;
		unsigned int column_;
};

#endif