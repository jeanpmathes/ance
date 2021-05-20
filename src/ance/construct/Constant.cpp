#include "Constant.h"

void ance::Constant::build(
	llvm::LLVMContext& c,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	build(c);
}

llvm::Value* ance::Constant::getNativeValue()
{
	return getNativeConstant();
}
