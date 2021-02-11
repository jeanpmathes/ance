#include "GlobalVariable.h"

#include <llvm/IR/GlobalValue.h>

#include "Constant.h"
#include "AccessModifier.h"
#include "Type.h"
#include "VoidType.h"

namespace llvm {
	class Constant;
}

ance::GlobalVariable::GlobalVariable(access_modifier access, std::string identifier, ance::Type* type, ance::Constant* constant_init, bool is_constant)
	: access_(access), identifier_(identifier), type_(type), constant_init_(constant_init), is_constant_(is_constant)
{
	assert(type != ance::VoidType::get());
	assert(type->get_name() == constant_init->get_type()->get_name());
}

llvm::GlobalVariable* ance::GlobalVariable::Build(llvm::LLVMContext& c, llvm::Module* m)
{
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
	return new llvm::GlobalVariable(*m, type_->get_native_type(c), is_constant_, linkage, native_initializer, identifier_);
}

ance::Type* ance::GlobalVariable::type()
{
	return constant_init_->get_type();
}