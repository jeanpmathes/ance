#include "AccessModifier.h"

llvm::GlobalValue::LinkageTypes convert(access_modifier access)
{
	llvm::GlobalValue::LinkageTypes linkage;

	switch (access)
	{
	case access_modifier::private_access:
		linkage = llvm::GlobalValue::LinkageTypes::PrivateLinkage;
		break;
	case access_modifier::public_access:
		linkage = llvm::GlobalValue::LinkageTypes::ExternalLinkage;
		break;
	}

	return linkage;
}