#include "ArrayType.h"
#include "Scope.h"

#include "GlobalScope.h"
#include "Value.h"
#include "Values.h"
#include "SizeType.h"
#include "WrappedNativeValue.h"
#include "CompileContext.h"

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

InternalStorage ance::ArrayType::storage()
{
	return InternalStorage::AS_POINTER;
}

bool ance::ArrayType::isIndexerDefined(Indexer)
{
	return true;
}

ance::Type* ance::ArrayType::getIndexerReturnType()
{
	return element_type_;
}

ance::Value* ance::ArrayType::buildGetIndexer(ance::Value* indexed, ance::Value* index, CompileContext* context)
{
	assert(indexed->getType() == this && "Indexed value has to be of native array type.");
	assert(index->getType() == ance::SizeType::get() && "Native array index has to be size type.");

	llvm::Value* element_ptr = buildGetElementPointer(indexed, index, context);
	llvm::Value* native_content = context->ir()->CreateLoad(element_ptr);

	llvm::Value* native_value = ance::Values::contentToNative(element_type_, native_content, context);

	return new ance::WrappedNativeValue(getIndexerReturnType(), native_value);
}

void ance::ArrayType::buildSetIndexer(
	ance::Value* indexed,
	ance::Value* index,
	ance::Value* value,
	CompileContext* context
)
{
	assert(indexed->getType() == this && "Indexed value has to be of native array type.");
	assert(index->getType() == ance::SizeType::get() && "Native array index has to be size type.");
	assert(value->getType() == element_type_ && "Assigned value has to be of the element type of this array.");

	value->buildContentValue(context);

	llvm::Value* element_ptr = buildGetElementPointer(indexed, index, context);
	llvm::Value* new_element_content = value->getContentValue();

	context->ir()->CreateStore(new_element_content, element_ptr);
}

llvm::Value* ance::ArrayType::buildGetElementPointer(
	ance::Value* indexed,
	ance::Value* index,
	CompileContext* context
) const
{
	indexed->buildNativeValue(context);
	index->buildContentValue(context);

	llvm::Value* zero = llvm::ConstantInt::get(llvm::Type::getInt64Ty(*context->llvmContext()), 0);
	llvm::Value* native_index = index->getContentValue();
	llvm::Value* indices[] = {zero, native_index};

	// Check if index smaller size.
	llvm::Value* native_size = llvm::ConstantInt::get(ance::SizeType::get()->getNativeType(*context->llvmContext()), size_);
	[[maybe_unused]] llvm::Value* in_bounds = context->ir()->CreateICmpULT(native_index, native_size);

	// todo: use in_bounds bool to throw exception

	// This is a pointer as the internal storage of arrays is using pointers.
	llvm::Value* array_ptr = indexed->getNativeValue();

	return context->ir()->CreateGEP(array_ptr, indices);
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
