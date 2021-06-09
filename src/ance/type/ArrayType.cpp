#include "ArrayType.h"
#include "Scope.h"

#include "GlobalScope.h"
#include "Value.h"
#include "Values.h"
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

llvm::Constant* ance::ArrayType::getDefaultContent(llvm::LLVMContext& c)
{
	std::vector<llvm::Constant*> content(size_, element_type_->getDefaultContent(c));
	return llvm::ConstantArray::get(type_, content);
}

llvm::Type* ance::ArrayType::getContentType(llvm::LLVMContext& c)
{
	if (!type_)
	{
		type_ = llvm::ArrayType::get(element_type_->getContentType(c), size_);
	}

	return type_;
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
	llvm::Value* indices[] = {zero, native_index};

	// This is a pointer as the internal storage of arrays is using pointers.
	llvm::Value* array_ptr = indexed->getNativeValue();

	llvm::Value* element_ptr = ir.CreateGEP(array_ptr, indices);
	llvm::Value* native_content = ir.CreateLoad(element_ptr);

	llvm::Value* native_value = ance::Values::contentToNative(element_type_, native_content, c, m, state, ir, di);

	return native_value;
}

void ance::ArrayType::buildSetIndexer(
	ance::Value* indexed,
	ance::Value* index,
	ance::Value* value,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	assert(indexed->getType() == this && "Indexed value has to be of native array type.");
	assert(index->getType() == ance::SizeType::get() && "Native array index has to be size type.");
	assert(value->getType() == element_type_ && "Assigned value has to be of the element type of this array.");

	indexed->build(c, m, state, ir, di);
	index->build(c, m, state, ir, di);
	value->build(c, m, state, ir, di);

	llvm::Value* zero = llvm::ConstantInt::get(llvm::Type::getInt64Ty(c), 0);
	llvm::Value* native_index = index->getContentValue(c, m, state, ir, di);
	llvm::Value* indices[] = {zero, native_index};

	// This is a pointer as the internal storage of arrays is using pointers.
	llvm::Value* array_ptr = indexed->getNativeValue();

	llvm::Value* element_ptr = ir.CreateGEP(array_ptr, indices);
	llvm::Value* new_element_content = value->getContentValue(c, m, state, ir, di);

	ir.CreateStore(new_element_content, element_ptr);
}

InternalStorage ance::ArrayType::storage()
{
	return InternalStorage::AS_POINTER;
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
