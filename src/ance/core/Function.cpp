#include "Function.h"

#include <utility>

ance::core::Function::Function(Signature signature, Type const& return_type, std::function<void(utility::List<utility::Shared<Value>> const&)> function)
    : signature_(std::move(signature))
    , return_type_(return_type)
    , function_(std::move(function))
{

}

void ance::core::Function::run(utility::List<utility::Shared<Value>> const& arguments) const
{
    function_(arguments);
}

ance::core::Identifier const& ance::core::Function::name() const
{
    return signature_.name();
}

ance::core::Signature const& ance::core::Function::signature() const
{
    return signature_;
}

ance::core::Type const& ance::core::Function::returnType() const
{
    return return_type_;
}

ance::core::Function* ance::core::Function::asFunction()
{
    return this;
}

ance::core::Function const* ance::core::Function::asFunction() const
{
    return this;
}

std::ostream& operator<<(std::ostream& out, ance::core::Function const& function)
{
    out << function.name();
    return out;
}
