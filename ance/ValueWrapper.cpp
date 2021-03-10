#include "ValueWrapper.h"

ance::ValueWrapper::ValueWrapper(ance::Type* type, llvm::Value* value) : type_(type), value_(value)
{
}

void ance::ValueWrapper::set_value(llvm::Value* value)
{
	value_ = value;
}

ance::Type* ance::ValueWrapper::get_type()
{
	return type_;
}

llvm::Value* ance::ValueWrapper::get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return value_;
}