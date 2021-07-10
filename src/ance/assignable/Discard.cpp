#include "Discard.h"

#include "Value.h"

void Discard::setScope(ance::Scope*)
{

}

void Discard::assign(
	ance::Value* value,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileContext* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	value->buildNativeValue(c, m, state, ir, di);
}


