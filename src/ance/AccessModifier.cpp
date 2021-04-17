#include "AccessModifier.h"

llvm::GlobalValue::LinkageTypes Convert(AccessModifier access)
{
	llvm::GlobalValue::LinkageTypes linkage;

	switch (access)
	{
	case AccessModifier::PRIVATE_ACCESS:
		linkage = llvm::GlobalValue::LinkageTypes::PrivateLinkage;
		break;
	case AccessModifier::PUBLIC_ACCESS:
		linkage = llvm::GlobalValue::LinkageTypes::ExternalLinkage;
		break;
	}

	return linkage;
}