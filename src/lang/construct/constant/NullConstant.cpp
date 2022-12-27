#include "NullConstant.h"

#include <memory>

#include "lang/type/NullPointerType.h"

lang::NullConstant::NullConstant() : type_(lang::NullPointerType::get()) {}

std::string lang::NullConstant::toString() const
{
    return "null";
}

lang::ResolvingHandle<lang::Type> lang::NullConstant::type()
{
    return type_;
}

lang::Type const& lang::NullConstant::type() const
{
    return type_;
}

llvm::Constant* lang::NullConstant::createContent(llvm::Module* m)
{
    return lang::NullPointerType::get()->getDefaultContent(*m);
}

bool lang::NullConstant::equals(lang::Constant const* other) const
{
    auto* other_null = dynamic_cast<NullConstant const*>(other);
    return other_null != nullptr;
}

Shared<lang::Constant> lang::NullConstant::clone() const
{
    return create();
}

Shared<lang::NullConstant> lang::NullConstant::create()
{
    return makeShared<lang::NullConstant>();
}
