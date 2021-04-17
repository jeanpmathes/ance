#include "WrappedNativeValue.h"

ance::WrappedNativeValue::WrappedNativeValue(ance::Type* type, llvm::Value* value) : type_(type), value_(value)
{
}

void ance::WrappedNativeValue::setValue(llvm::Value* value)
{
	value_ = value;
}

ance::Type* ance::WrappedNativeValue::getType()
{
	return type_;
}

llvm::Value* ance::WrappedNativeValue::getValue(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	return value_;
}