#include "Constant.h"

llvm::Value* ance::Constant::getValue(
	llvm::LLVMContext& c,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	build(c);
	return getNativeConstant();
}
