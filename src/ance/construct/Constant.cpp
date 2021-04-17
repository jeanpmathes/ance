#include "Constant.h"
llvm::Value *ance::Constant::getValue(llvm::LLVMContext &c, llvm::Module *m, CompileState *state, llvm::IRBuilder<> &ir, llvm::DIBuilder *di) {
    return getConstant(c);
}
