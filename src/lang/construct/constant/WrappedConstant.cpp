#include "WrappedConstant.h"

lang::WrappedConstant::WrappedConstant(lang::ResolvingHandle<lang::Type> type, llvm::Constant* constant)
    : type_(std::move(type))
    , constant_(constant)
{}

std::string lang::WrappedConstant::toString() const
{
    std::string              str;
    llvm::raw_string_ostream stream(str);
    constant_->print(stream);

    return "/*" + stream.str() + "*/";
}

lang::ResolvingHandle<lang::Type> lang::WrappedConstant::type()
{
    return type_;
}

lang::Type const& lang::WrappedConstant::type() const
{
    return type_;
}

Shared<lang::Constant> lang::WrappedConstant::createContent(CompileContext&)
{
    throw std::logic_error("Wrapped constants cannot create a content constant");
}

llvm::Constant* lang::WrappedConstant::getWrappedConstant() const
{
    return constant_;
}

bool lang::WrappedConstant::equals(lang::Constant const* other) const
{
    if (auto* wrapped = dynamic_cast<WrappedConstant const*>(other); wrapped != nullptr)
        return constant_ == wrapped->constant_;

    return false;
}

Shared<lang::Constant> lang::WrappedConstant::clone(lang::Context& new_context) const
{
    return makeShared<WrappedConstant>(type_->getUndefinedTypeClone(new_context), constant_);
}
