#include "PointerType.h"

#include <llvm/IR/Constants.h>

#include "Application.h"
#include "GlobalScope.h"
#include "VoidType.h"
#include "Value.h"
#include "SizeType.h"

ance::PointerType::PointerType(ance::Type* element_type)
	: element_type_(element_type)
{

}

std::string ance::PointerType::getName()
{
	return element_type_->getName() + "*";
}

llvm::Constant* ance::PointerType::getDefault(llvm::LLVMContext& c)
{
	return llvm::ConstantPointerNull::get(getContentType(c));
}

llvm::PointerType* ance::PointerType::getContentType(llvm::LLVMContext& c)
{
	llvm::Type* native_type;

	if (element_type_ == ance::VoidType::get())
	{
		native_type = llvm::Type::getInt8PtrTy(c);
	}
	else
	{
		native_type = element_type_->getNativeType(c);
	}

	return llvm::PointerType::get(native_type, 0);
}

ance::Type* ance::PointerType::get(Application& app, ance::Type* element_type)
{
	auto* type = new ance::PointerType(element_type);
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

bool ance::PointerType::isIndexerDefined(Indexer)
{
	return true;
}

ance::Type* ance::PointerType::getIndexerReturnType()
{
	return element_type_;
}

llvm::Value* ance::PointerType::buildGetIndexer(
	ance::Value* indexed,
	ance::Value* index,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	assert(indexed->getType() == this && "Indexed value has to be of pointer type.");
	assert(index->getType() == ance::SizeType::get() && "Pointer index has to be size type.");

	indexed->build(c, m, state, ir, di);
	index->build(c, m, state, ir, di);

	llvm::Value* native_index = index->getContentValue(c, m, state, ir, di);
	llvm::Value* indices[] = { native_index };

	llvm::Value* ptr = indexed->getNativeValue();

	llvm::Value* element_ptr = ir.CreateGEP(ptr, indices);
	llvm::Value* native_value = ir.CreateLoad(element_ptr);

	return native_value;
}
