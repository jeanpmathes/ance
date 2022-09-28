#include "NullConstant.h"

#include <memory>

#include "lang/type/NullPointerType.h"

std::string lang::NullConstant::toString() const
{
    return "null";
}

lang::ResolvingHandle<lang::Type> lang::NullConstant::type() const
{
    return lang::NullPointerType::get();
}

llvm::Constant* lang::NullConstant::buildContent(llvm::Module* m)
{
    return lang::NullPointerType::get()->getDefaultContent(*m);
}

bool lang::NullConstant::equals(const lang::Constant* other) const
{
    auto* other_null = dynamic_cast<const NullConstant*>(other);
    return other_null != nullptr;
}

std::shared_ptr<lang::NullConstant> lang::NullConstant::create()
{
    return std::make_shared<lang::NullConstant>();
}
