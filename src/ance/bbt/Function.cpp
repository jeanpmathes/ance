#include "Function.h"

#include <utility>

#include "ance/core/Type.h"

ance::bbt::Function::Function(core::Signature signature, core::Type const& return_type, utility::Shared<Flow> body)
    : Value(core::Type::Function())
    , signature_(std::move(signature))
    , return_type_(return_type)
    , body_(std::move(body))
{

}

ance::bbt::Function::Function(core::Signature signature, core::Type const& return_type, utility::Owned<Flow> body)
    : Value(core::Type::Function())
    , signature_(std::move(signature))
    , return_type_(return_type)
    , body_(utility::Shared(*utility::Owned<Flow>::release(std::move(body))))
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

std::string ance::bbt::Function::toString() const
{
    return "@" + std::string(signature_.name().text());
}

ance::utility::Shared<ance::bbt::Value> ance::bbt::Function::clone() const
{
    Function* mutable_this = const_cast<Function*>(this); // Because the value class is immutable, a clone does not violate constness.

    return utility::makeShared<Function>(signature_, return_type_, mutable_this->body_);
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Function const& function)
{
    out << function.name();
    return out;
}
