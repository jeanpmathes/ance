#include "Function.h"

#include <utility>

ance::core::Function::Function(Signature const& signature, std::function<void(utility::List<bool> const&)> function)
    : signature_(signature), function_(std::move(function))
{

}
void ance::core::Function::run(utility::List<bool> const& arguments) const
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

std::ostream& operator<<(std::ostream& out, ance::core::Function const& function)
{
    out << function.name();
    return out;
}
