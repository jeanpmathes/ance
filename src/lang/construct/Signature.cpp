#include "Signature.h"

#include <utility>

lang::Signature::Signature(Identifier const& name, std::vector<Shared<lang::Parameter>> parameters)
    : function_name_(name)
    , parameters_(std::move(parameters))
{
}

size_t lang::Signature::getParameterCount() const
{
    return parameters_.size();
}

lang::Signature lang::Signature::fromParameters(Identifier name, std::vector<Shared<lang::Parameter>> parameters)
{
    return Signature(name, std::move(parameters));
}

bool lang::Signature::isSame(std::vector<std::reference_wrapper<lang::Type const>> const& arguments) const
{
    if (parameters_.size() != arguments.size()) return false;

    auto types = llvm::zip(parameters_, arguments);
    return std::all_of(types.begin(), types.end(), [](auto pair) {
        return lang::Type::areSame(std::get<0>(pair)->type(), std::get<1>(pair));
    });
}

bool lang::Signature::isMatching(std::vector<std::reference_wrapper<lang::Type const>> const& arguments) const
{
    if (parameters_.size() != arguments.size()) return false;

    auto types = llvm::zip(parameters_, arguments);
    return std::all_of(types.begin(), types.end(), [](auto pair) {
        return lang::Type::isMatching(std::get<0>(pair)->type(), std::get<1>(pair));
    });
}

std::string const& lang::Signature::getMangledName() const
{
    if (!mangled_name_.empty()) return mangled_name_;

    mangled_name_ = function_name_ + "$overload(";

    bool is_first = true;
    for (auto& parameter : parameters_)
    {
        if (!is_first) { mangled_name_ += "$"; }

        is_first = false;
        mangled_name_ += parameter->type().getMangledName();
    }

    mangled_name_ += ")";

    return mangled_name_;
}

std::string lang::Signature::toString() const
{
    std::string string = function_name_ + " (";

    bool is_first = true;
    for (auto& parameter : parameters_)
    {
        if (!is_first) { string += ", "; }

        is_first = false;
        string += parameter->type().getActualType().name().text();
    }

    string += ")";
    return string;
}

bool lang::Signature::operator==(lang::Signature const& other) const
{
    return areSame(*this, other);
}

bool lang::Signature::operator!=(lang::Signature const& other) const
{
    return !areSame(*this, other);
}

bool lang::Signature::areSame(lang::Signature const& a, lang::Signature const& b)
{
    if (a.function_name_.text() != b.function_name_.text()) return false;
    if (a.parameters_.size() != b.parameters_.size()) return false;

    auto parameters = llvm::zip(a.parameters_, b.parameters_);
    return std::all_of(parameters.begin(), parameters.end(), [](auto pair) {
        return lang::Type::areSame(std::get<0>(pair)->type(), std::get<1>(pair)->type());
    });
}
