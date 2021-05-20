#include "Constant.h"

#include "Type.h"

void ance::Constant::build(llvm::LLVMContext& c)
{
	assert(!content_constant_ && "A constant may only be built once.");

	content_constant_ = buildContent(c);
}

llvm::Constant * ance::Constant::getContentConstant()
{
	assert(content_constant_ && "Constant has to be built before accessing content constant.");
	return content_constant_;
}

void ance::Constant::build(
	llvm::LLVMContext& c,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder*
)
{
	build(c);

	switch (getType()->storage())
	{
		case InternalStorage::AS_TEMPORARY:
		{
			native_value_ = content_constant_;
			break;
		}
		case InternalStorage::AS_POINTER:
		{
			native_value_ = ir.CreateAlloca(getType()->getContentType(c), nullptr);
			ir.CreateStore(content_constant_, native_value_);
			break;
		}
	}
}

llvm::Value* ance::Constant::getNativeValue()
{
	assert(native_value_ && "Constant (as value) has to be built before accessing native value.");
	return native_value_;
}

llvm::Value* ance::Constant::getContentValue(
	llvm::LLVMContext&,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	return getContentConstant();
}
