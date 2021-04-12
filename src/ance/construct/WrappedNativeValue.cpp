#include "WrappedNativeValue.h"

ance::WrappedNativeValue::WrappedNativeValue(ance::Type* type, llvm::Value* value) : type_(type), value_(value)
{
}

void ance::WrappedNativeValue::set_value(llvm::Value* value)
{
	value_ = value;
}

ance::Type* ance::WrappedNativeValue::get_type()
{
	return type_;
}

llvm::Value* ance::WrappedNativeValue::get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return value_;
}