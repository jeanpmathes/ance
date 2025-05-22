#include "Function.h"

#include <utility>

ance::core::Function::Function(Signature const& signature, Type const& return_type, std::function<void(utility::List<utility::Shared<Value>> const&)> function)
    : signature_(signature)
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

std::ostream& operator<<(std::ostream& out, ance::core::Function const& function)
{
    out << function.name();
    return out;
}
