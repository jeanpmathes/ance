#include "GlobalVariable.h"

#include <utility>

#include <llvm/IR/GlobalValue.h>

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

void ance::GlobalVariable::buildGlobal(llvm::LLVMContext& c, llvm::Module* m)
{
	assert(type() != ance::VoidType::get());
	assert(type() == constant_init_->getType());

	llvm::GlobalValue::LinkageTypes linkage = Convert(access_);

	constant_init_->build(c);
	llvm::Constant* native_initializer = constant_init_->getNativeConstant();
	native_variable_ = new llvm::GlobalVariable(
		*m, type()->getNativeType(c),
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
	auto* const value_type = static_cast<llvm::PointerType*>(native_variable_->getType())->getElementType();
	llvm::Value* value = ir.CreateLoad(value_type, native_variable_);
	value->setName(identifier());
	return new ance::WrappedNativeValue(type(), value);
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

	value->build(c, m, state, ir, di);
	ir.CreateStore(value->getNativeValue(), native_variable_);
}