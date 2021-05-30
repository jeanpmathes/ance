#ifndef ANCE_SRC_ANCE_ASSIGNABLE_DISCARD_H_
#define ANCE_SRC_ANCE_ASSIGNABLE_DISCARD_H_

#include "Assignable.h"

class Discard : public Assignable
{
	public:
		void setScope(ance::Scope* scope) override;

		void assign(ance::Value* value, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di) override;
};

#endif
