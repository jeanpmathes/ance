#include "Function.h"

#include <utility>

#include "ance/bbt/Type.h"

namespace ance::bbt
{
    Function::Function(Signature signature, utility::Shared<Type> return_type, utility::Shared<Flow> body)
    : Value(Type::Function())
    , signature_(std::move(signature))
    , return_type_(std::move(return_type))
    , body_(std::move(body))
    {

    }

    Function::Function(Signature signature, utility::Shared<Type> return_type, utility::Owned<Flow> body)
        : Value(Type::Function())
        , signature_(std::move(signature))
        , return_type_(std::move(return_type))
        , body_(utility::Shared(*utility::Owned<Flow>::release(std::move(body))))
    {}

    core::Identifier const& Function::name() const
    {
        return signature_.name();
    }

    Signature Function::signature()
    {
        return signature_;
    }

    Signature const& Function::signature() const
    {
        return signature_;
    }

    utility::Shared<Type> Function::returnType()
    {
        return return_type_;
    }

    Type const& Function::returnType() const
    {
        return *return_type_;
    }

    Flow const& Function::body() const
    {
        return *body_;
    }

    std::string Function::toString() const
    {
        return "@" + std::string(signature_.name().text());
    }
}

std::ostream& operator<<(std::ostream& out, ance::bbt::Function const& function)
{
    out << function.name();
    return out;
}
