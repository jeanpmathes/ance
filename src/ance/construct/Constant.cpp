#include "Constant.h"
llvm::Value *ance::Constant::get_value(llvm::LLVMContext &c, llvm::Module *m, CompileState *state, llvm::IRBuilder<> &ir, llvm::DIBuilder *di) {
    return get_constant(c);
}
