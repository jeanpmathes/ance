#include "GlobalVariable.h"

#include <llvm/IR/GlobalValue.h>

#include "Constant.h"
#include "AccessModifier.h"

namespace llvm {
	class Constant;
}

ance::GlobalVariable::GlobalVariable(access_modifier access, std::string identifier, ance::Constant* constant_init, bool is_constant)
	: access_(access), identifier_(identifier), constant_init_(constant_init), is_constant_(is_constant)
{
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
	return new llvm::GlobalVariable(*m, native_initializer->getType(), is_constant_, linkage, native_initializer, identifier_);
}