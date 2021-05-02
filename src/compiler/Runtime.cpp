#include "Runtime.h"

#include <stdexcept>

#include "Type.h"
#include "CompileState.h"
#include "SizeType.h"
#include "PointerType.h"
#include "CompileState.h"

void Runtime::init(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	llvm::Type* allocate_dynamic_params[] =
		{llvm::Type::getInt32Ty(c), ance::SizeType::get()->getNativeType(c)};
	allocate_dynamic_type_ = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(c), allocate_dynamic_params, false);
	allocate_dynamic_ = llvm::Function::Create(
		allocate_dynamic_type_,
		llvm::GlobalValue::LinkageTypes::ExternalLinkage,
		"GlobalAlloc",
		m
	);
}

llvm::Value* Runtime::allocate(
	Runtime::Allocator allocation,
	ance::Type* type,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	switch (allocation)
	{
		case AUTOMATIC:
			return allocateAutomatic(type, c, m, state, ir, di);
		case DYNAMIC:
			return allocateDynamic(type, c, m, state, ir, di);
		default:
			throw std::invalid_argument("Unsupported allocation type.");
	}
}

llvm::Value* Runtime::allocateAutomatic(
	ance::Type* type,
	llvm::LLVMContext& c,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder*
)
{
	return ir.CreateAlloca(type->getNativeType(c));
}

llvm::Value* Runtime::allocateDynamic(
	ance::Type* type,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder*
)
{
	llvm::Value* args[] = {llvm::ConstantInt::get(llvm::Type::getInt32Ty(c), 0x0040, false), llvm::ConstantInt::get(
		ance::SizeType::get()->getNativeType(c),
		type->getSize(m).getFixedSize(),
		false
	)};

	llvm::Value* opaque_ptr = ir.CreateCall(allocate_dynamic_type_, allocate_dynamic_, args);
	return ir.CreateBitCast(opaque_ptr, ance::PointerType::get(*state->application_, type)->getNativeType(c));
}
