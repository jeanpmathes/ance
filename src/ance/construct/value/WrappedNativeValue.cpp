#include "WrappedNativeValue.h"

ance::WrappedNativeValue::WrappedNativeValue(ance::Type* type, llvm::Value* value)
	: type_(type), value_(value)
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

void ance::WrappedNativeValue::buildNativeValue(
	llvm::LLVMContext&,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
}

llvm::Value* ance::WrappedNativeValue::getNativeValue()
{
	return value_;
}
