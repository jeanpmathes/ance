#include "Function.h"

#include <utility>

ance::bbt::Function::Function(core::Signature signature, core::Type const& return_type, utility::Owned<Flow> body)
    : signature_(std::move(signature))
    , return_type_(return_type)
    , body_(std::move(body))
{}

ance::core::Identifier const& ance::bbt::Function::name() const
{
    return signature_.name();
}

ance::core::Signature const& ance::bbt::Function::signature() const
{
    return signature_;
}

ance::core::Type const& ance::bbt::Function::returnType() const
{
    return return_type_;
}

ance::bbt::Flow const& ance::bbt::Function::body() const
{
    return *body_;
}

void* ance::bbt::Function::asFunction()
{
    return this;
}

void const* ance::bbt::Function::asFunction() const
{
    return this;
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Function const& function)
{
    out << function.name();
    return out;
}
