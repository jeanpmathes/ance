#include "Constant.h"

#include "Type.h"

void ance::Constant::build(llvm::LLVMContext& c)
{
	assert(!content_constant_ && "A constant may only be built once.");
	assert(!native_constant_ && "A constant may only be built once.");

	content_constant_ = buildContent(c);

	switch (getType()->storage())
	{
		case InternalStorage::AS_TEMPORARY:
		{
			native_constant_ = content_constant_;
			break;
		}
		case InternalStorage::AS_POINTER:
		{
			llvm::Constant* zero = llvm::ConstantInt::get(llvm::Type::getInt64Ty(c), 0);
			llvm::Constant* indices[] = {zero, zero};
			native_constant_ = llvm::ConstantExpr::getInBoundsGetElementPtr(stored_constant_->getType(), stored_constant_, indices);
			break;
		}
	}
}

llvm::Constant * ance::Constant::getNativeConstant()
{
	assert(native_constant_ && "Constant has to be built before accessing native constant.");
	return native_constant_;
}

llvm::Constant * ance::Constant::getContentConstant()
{
	assert(content_constant_ && "Constant has to be built before accessing stored constant.");
	return content_constant_;
}

void ance::Constant::build(
	llvm::LLVMContext& c,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	build(c);
}

llvm::Value* ance::Constant::getNativeValue()
{
	return getNativeConstant();
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
