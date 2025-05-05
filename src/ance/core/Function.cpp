#include "Function.h"

#include <utility>

ance::core::Function::Function(Identifier const& name, std::function<void()> function) : name_(name), function_(std::move(function)) {}

void ance::core::Function::run() const
{
    function_();
}

ance::core::Identifier const& ance::core::Function::name() const
{
    return name_;
}

std::ostream& operator<<(std::ostream& out, ance::core::Function const& function)
{
    out << function.name();
    return out;
}
