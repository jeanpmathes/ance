#include "GlobalVariable.h"

#include <llvm/IR/GlobalValue.h>

#include "Constant.h"
#include "AccessModifier.h"
#include "Type.h"
#include "VoidType.h"

namespace llvm {
	class Constant;
}

ance::GlobalVariable::GlobalVariable(ance::Scope* containing_scope, access_modifier access, std::string identifier, ance::Type* type, ance::Constant* constant_init, bool is_constant)
	: Variable(containing_scope, identifier, type, is_constant), access_(access), constant_init_(constant_init), native_variable_(nullptr)
{
}

ance::GlobalVariable::GlobalVariable(std::string identifier)
	: Variable(identifier), access_(access_modifier::private_access), constant_init_(nullptr), native_variable_(nullptr)
{
}

void ance::GlobalVariable::define_global(ance::Scope* containing_scope, access_modifier access, ance::Type* type, ance::Constant* constant_init, bool is_constant)
{
	this->define(containing_scope, type, is_constant);

	access_ = access;
	constant_init_ = constant_init;
}

void ance::GlobalVariable::build_global(llvm::LLVMContext& c, llvm::Module* m)
{
	assert(type() != ance::VoidType::get());
	assert(type()->get_name() == constant_init_->get_type()->get_name());

	llvm::GlobalValue::LinkageTypes linkage;

	switch (access_)
	{
	case access_modifier::private_access:
		linkage = llvm::GlobalValue::LinkageTypes::PrivateLinkage;
		break;
	case access_modifier::public_access:
		linkage = llvm::GlobalValue::LinkageTypes::ExternalLinkage;
		break;
	}

	llvm::Constant* native_initializer = constant_init_->get_constant(c);
	native_variable_ = new llvm::GlobalVariable(*m, type()->get_native_type(c), is_constant(), linkage, native_initializer, identifier());
}

llvm::Value* ance::GlobalVariable::get_value(llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	const auto value_type = static_cast<llvm::PointerType*>(native_variable_->getType())->getElementType();
	return ir.CreateLoad(value_type, native_variable_);
}

void ance::GlobalVariable::set_value(llvm::Value* value, llvm::LLVMContext& c, llvm::Module* m, CompileState* state, llvm::IRBuilder<>& ir, llvm::DIBuilder* di)
{
	assert(!is_constant());
	ir.CreateStore(value, native_variable_);
}