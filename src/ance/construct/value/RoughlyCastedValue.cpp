#include "RoughlyCastedValue.h"

#include "Type.h"

ance::RoughlyCastedValue::RoughlyCastedValue(ance::Type* target_type, ance::Value* original)
	: target_type_(target_type), original_(original)
{
	assert(target_type->storage() == original->getType()->storage());
}

ance::Type* ance::RoughlyCastedValue::getType()
{
	return target_type_;
}

void ance::RoughlyCastedValue::buildNativeValue(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	assert(target_type_->getNativeType(c) == original_->getType()->getNativeType(c) && "Native type has to be equal.");
	original_->buildNativeValue(c, m, state, ir, di);
}

llvm::Value* ance::RoughlyCastedValue::getNativeValue()
{
	return original_->getNativeValue();
}
