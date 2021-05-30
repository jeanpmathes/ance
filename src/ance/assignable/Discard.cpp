#include "Discard.h"

#include "Value.h"

void Discard::setScope(ance::Scope*)
{

}

void Discard::assign(
	ance::Value* value,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	value->build(c, m, state, ir, di);
}


