#include "BuildableConstantExpression.h"
#include "Constant.h"

llvm::Value* BuildableConstantExpression::build(
	llvm::LLVMContext& c,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	return buildConstant(c);
}
