#include "BuildableConstantExpression.h"
#include "Constant.h"

llvm::Value* BuildableConstantExpression::build(llvm::LLVMContext &c, llvm::Module *m, CompileState *state, llvm::IRBuilder<> &ir, llvm::DIBuilder *di)
{
    return buildConstant(c);
}
