#include "BuildableConstantExpression.h"
#include "Constant.h"

ance::Value *BuildableConstantExpression::get_value()
{
    return get_constant_value();
}

llvm::Value *BuildableConstantExpression::build(llvm::LLVMContext &c, llvm::Module *m, CompileState *state, llvm::IRBuilder<> &ir, llvm::DIBuilder *di)
{
    return build_constant(c);
}
