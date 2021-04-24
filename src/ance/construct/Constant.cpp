#include "Constant.h"

llvm::Value* ance::Constant::getValue(
	llvm::LLVMContext& c,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	return getConstant(c);
}
