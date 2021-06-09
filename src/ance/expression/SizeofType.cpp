#include "SizeofType.h"

#include "CompileState.h"
#include "SizeType.h"

SizeofType::SizeofType(ance::Type* type)
	: type_(type)
{
}

ance::Type* SizeofType::getType()
{
	return ance::SizeType::get();
}

ance::Value* SizeofType::getValue()
{
	return return_value_;
}

llvm::Value* SizeofType::build(
	llvm::LLVMContext&,
	llvm::Module* m,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	return ance::SizeType::buildValue(type_->getNativeSize(m));
}