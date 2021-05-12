#include "SizeofType.h"

#include "CompileState.h"
#include "ExpressionBackedValue.h"
#include "SizeType.h"

SizeofType::SizeofType(ance::Type* type)
	: return_value_(new ance::ExpressionBackedValue(this)), type_(type)
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
	return ance::SizeType::get()->buildValue(type_->getSize(m));
}