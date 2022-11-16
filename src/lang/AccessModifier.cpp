#include "lang/AccessModifier.h"

lang::AccessModifier::operator Value() const
{
    return value_;
}

std::string lang::AccessModifier::toString() const
{
    switch (value_)
    {
        case AccessModifier::PRIVATE_ACCESS:
            return "private";

        case AccessModifier::PUBLIC_ACCESS:
            return "public";
    }
}

llvm::GlobalValue::LinkageTypes lang::AccessModifier::linkage()
{
    llvm::GlobalValue::LinkageTypes linkage;

    switch (value_)
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
