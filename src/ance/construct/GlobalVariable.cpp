#include "GlobalVariable.h"

#include <utility>

#include "Constant.h"
#include "AccessModifier.h"
#include "Type.h"
#include "VoidType.h"
#include "WrappedNativeValue.h"

namespace llvm
{
class Constant;
}

ance::GlobalVariable::GlobalVariable(
	ance::Scope* containing_scope,
	AccessModifier access,
	std::string identifier,
	ance::Type* type,
	ance::Constant* constant_init,
	bool is_constant
)
	: Variable(containing_scope, std::move(identifier), type, is_constant),
	  access_(access),
	  constant_init_(constant_init)
{
}

ance::GlobalVariable::GlobalVariable(std::string identifier)
	: Variable(std::move(identifier)), access_(AccessModifier::PRIVATE_ACCESS)
{
}

void ance::GlobalVariable::defineGlobal(
	ance::Scope* containing_scope,
	AccessModifier access,
	ance::Type* type,
	ance::Constant* constant_init,
	bool is_constant
)
{
	this->define(containing_scope, type, is_constant);

	access_ = access;
	constant_init_ = constant_init;
}

void ance::GlobalVariable::buildGlobal(llvm::Module* m)
{
	assert(type() != ance::VoidType::get());
	assert(type() == constant_init_->getType());

	llvm::GlobalValue::LinkageTypes linkage = Convert(access_);

	constant_init_->buildContentConstant(m);
	llvm::Constant* native_initializer = constant_init_->getContentConstant();
	native_variable_ = new llvm::GlobalVariable(
		*m, type()->getContentType(m->getContext()),
		isConstant(), linkage, native_initializer, identifier());
}

ance::Value* ance::GlobalVariable::getValue(
	llvm::LLVMContext&,
	llvm::Module*,
	CompileState*,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder*
)
{
	switch (type()->storage())
	{
		case InternalStorage::AS_TEMPORARY:
		{
			auto* const value_type = static_cast<llvm::PointerType*>(native_variable_->getType())->getElementType();
			llvm::Value* value = ir.CreateLoad(value_type, native_variable_);
			value->setName(identifier());
			return new ance::WrappedNativeValue(type(), value);
		}

		case InternalStorage::AS_POINTER:
		{
			return new ance::WrappedNativeValue(type(), native_variable_);
		}
	}
}

void ance::GlobalVariable::setValue(
	ance::Value* value,
	llvm::LLVMContext& c,
	llvm::Module* m,
	CompileState* state,
	llvm::IRBuilder<>& ir,
	llvm::DIBuilder* di
)
{
	assert(!isConstant());
	assert(type() == value->getType() && "Assignment types have to match.");

	value->buildContentValue(c, m, state, ir, di);

	llvm::Value* content = value->getContentValue();
	ir.CreateStore(content, native_variable_);
}