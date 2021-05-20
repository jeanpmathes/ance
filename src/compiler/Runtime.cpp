#include "Runtime.h"

#include <stdexcept>

#include "Type.h"
#include "Value.h"
#include "CompileState.h"
#include "SizeType.h"
#include "PointerType.h"

void Runtime::init(
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState*,
	llvm::IRBuilder<>&,
	llvm::DIBuilder*
)
{
	// Setup dynamic memory allocation call.
	llvm::Type* allocate_dynamic_params[] =
		{llvm::Type::getInt32Ty(c), ance::SizeType::get()->getNativeType(c)};
	allocate_dynamic_type_ = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(c), allocate_dynamic_params, false);
	allocate_dynamic_ = llvm::Function::Create(
		allocate_dynamic_type_,
		llvm::GlobalValue::LinkageTypes::ExternalLinkage,
		"GlobalAlloc",
		m
	);

	// Setup dynamic memory delete call.
	llvm::Type* delete_dynamic_params[] = {llvm::Type::getInt8PtrTy(c)};
	delete_dynamic_type_ = llvm::FunctionType::get(llvm::Type::getInt8PtrTy(c), delete_dynamic_params, false);
	delete_dynamic_ = llvm::Function::Create(
		delete_dynamic_type_,
		llvm::GlobalValue::LinkageTypes::ExternalLinkage,
		"GlobalFree",
		m
	);
}

llvm::Value* Runtime::allocate(
	Runtime::Allocator allocation,
	ance::Type* type,
	ance::Value* count,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	if (count)
	{
		assert(count->getType() == ance::SizeType::get() && "Count parameter of allocation should be of type size.");
	}

	switch (allocation)
	{
		case AUTOMATIC:
			return allocateAutomatic(type, count, c, m, state, ir, di);
		case DYNAMIC:
			return allocateDynamic(type, count, c, m, state, ir, di);
		default:
			throw std::invalid_argument("Unsupported allocation type.");
	}
}

void Runtime::deleteDynamic(
	ance::Value* value,
	bool,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	ance::Type* type = value->getType();
	assert(dynamic_cast<ance::PointerType*>(type) && "Type of value to delete has to be pointer type.");

	value->build(c, m, state, ir, di);

	llvm::Value* ptr = value->getNativeValue();
	llvm::Value* opaque_ptr = ir.CreateBitCast(ptr, llvm::Type::getInt8PtrTy(c));

	llvm::Value* args[] = {opaque_ptr};

	ir.CreateCall(delete_dynamic_type_, delete_dynamic_, args);
}

llvm::Value* Runtime::allocateAutomatic(
	ance::Type* type,
	ance::Value* count,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	llvm::Value* count_value = nullptr;

	if (count)
	{
		count->build(c, m, state, ir, di);
		count_value = count->getNativeValue();
	}

	return ir.CreateAlloca(type->getNativeType(c), count_value);
}

llvm::Value* Runtime::allocateDynamic(
	ance::Type* type,
	ance::Value* count,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	// Set the zero init flag.
	llvm::Value* flags = llvm::ConstantInt::get(llvm::Type::getInt32Ty(c), 0x0040, false);

	// Calculate the size to allocate.
	llvm::Value* size;

	if (count)
	{
		llvm::Value* element_size =
			llvm::ConstantInt::get(ance::SizeType::get()->getNativeType(c), type->getSize(m).getFixedSize(), false);
		count->build(c, m, state, ir, di);
		llvm::Value* element_count = count->getNativeValue();

		size = ir.CreateMul(element_size, element_count);
	}
	else
	{
		size = llvm::ConstantInt::get(ance::SizeType::get()->getNativeType(c), type->getSize(m).getFixedSize(), false);
	}

	llvm::Value* args[] = {flags, size};

	llvm::Value* opaque_ptr = ir.CreateCall(allocate_dynamic_type_, allocate_dynamic_, args);
	return ir.CreateBitCast(opaque_ptr, ance::PointerType::get(*state->application_, type)->getNativeType(c));
}
