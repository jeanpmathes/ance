#include "ArrayType.h"
#include "Scope.h"

#include <llvm/IR/Constants.h>
#include <llvm/IR/DerivedTypes.h>

#include "GlobalScope.h"
#include "Value.h"
#include "SizeType.h"

ance::ArrayType::ArrayType(Type* element_type, const uint64_t size)
	:
	size_(size),
	element_type_(element_type)
{
}

std::string ance::ArrayType::getName()
{
	return element_type_->getName() + "[" + std::to_string(size_) + "]";
}

llvm::Constant* ance::ArrayType::getDefault(llvm::LLVMContext& c)
{
	llvm::Constant* consts[size_];
	std::fill_n(consts, size_, element_type_->getDefault(c));

	if (!type_) getNativeType(c);

	llvm::ArrayRef<llvm::Constant*> content = llvm::ArrayRef<llvm::Constant*>(&consts[0], size_);

	return llvm::ConstantArray::get(type_, content);
}

llvm::Type* ance::ArrayType::getContentType(llvm::LLVMContext& c)
{
	if (!type_)
	{
		type_ = llvm::ArrayType::get(element_type_->getNativeType(c), size_);
	}

	return type_;
}

ance::Type* ance::ArrayType::get(Application& app, Type* element_type, uint64_t size)
{
	auto* type = new ance::ArrayType(element_type, size);
	std::string type_name = type->getName();

	if (app.globalScope()->isTypeRegistered(type_name))
	{
		delete type;
		return app.globalScope()->getType(type_name);
	}
	else
	{
		app.globalScope()->registerType(type);
		return type;
	}
}

bool ance::ArrayType::isIndexerDefined(Indexer)
{
	return true;
}

ance::Type* ance::ArrayType::getIndexerReturnType()
{
	return element_type_;
}

llvm::Value* ance::ArrayType::buildGetIndexer(
	ance::Value* indexed,
	ance::Value* index,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	assert(indexed->getType() == this && "Indexed value has to be of native array type.");
	assert(index->getType() == ance::SizeType::get() && "Native array index has to be size type.");

	indexed->build(c, m, state, ir, di);
	index->build(c, m, state, ir, di);

	llvm::Value* zero = llvm::ConstantInt::get(llvm::Type::getInt64Ty(c), 0);
	llvm::Value* native_index = index->getContentValue(c, m, state, ir, di);
	llvm::Value* indices[] = { zero, native_index };

	// This is a pointer as the internal storage of arrays is using pointers.
	llvm::Value* array_ptr = indexed->getNativeValue();

	llvm::Value* element_ptr = ir.CreateGEP(array_ptr, indices);
	llvm::Value* native_value = ir.CreateLoad(element_ptr);

	return native_value;
}

InternalStorage ance::ArrayType::storage()
{
	return InternalStorage::AS_POINTER;
}
