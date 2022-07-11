#include "Signature.h"

lang::Signature::Signature(const Identifier& name, std::vector<lang::ResolvingHandle<lang::Type>>& types)
    : function_name_(name)
    , types_(types)
{}

size_t lang::Signature::getParameterCount() const
{
    return types_.size();
}

lang::Signature lang::Signature::fromParameters(Identifier                                           name,
                                                const std::vector<std::shared_ptr<lang::Parameter>>& parameters)
{
    std::vector<ResolvingHandle<Type>> types;

    types.reserve(parameters.size());
    for (auto& parameter : parameters) { types.push_back(parameter->type()); }

    return Signature(name, types);
}

bool lang::Signature::isSame(const std::vector<lang::ResolvingHandle<lang::Type>>& arguments) const
{
    if (types_.size() != arguments.size()) return false;

    auto types = llvm::zip(types_, arguments);
    return std::all_of(types.begin(), types.end(), [](const auto& pair) {
        return lang::Type::areSame(std::get<0>(pair), std::get<1>(pair));
    });
}

bool lang::Signature::isMatching(const std::vector<lang::ResolvingHandle<lang::Type>>& arguments) const
{
    if (types_.size() != arguments.size()) return false;

    auto types = llvm::zip(types_, arguments);
    return std::all_of(types.begin(), types.end(), [](const auto& pair) {
        return lang::Type::isMatching(std::get<0>(pair), std::get<1>(pair));
    });
}

const std::string& lang::Signature::getMangledName()
{
    if (!mangled_name_.empty()) return mangled_name_;

    mangled_name_ = function_name_ + "$overload(";

    bool is_first = true;
    for (auto& type : types_)
    {
        if (!is_first) { mangled_name_ += "$"; }

        is_first = false;
        mangled_name_ += type->getMangledName();
    }

    mangled_name_ += ")";

    return mangled_name_;
}

std::string lang::Signature::toString() const
{
    std::string string = function_name_ + " (";

    bool is_first = true;
    for (auto& type : types_)
    {
        if (!is_first) { string += ", "; }

        is_first = false;
        string += type->getActualType()->name().text();
    }

    string += ")";
    return string;
}

bool lang::Signature::operator==(const lang::Signature& other) const
{
    return areSame(*this, other);
}

bool lang::Signature::operator!=(const lang::Signature& other) const
{
    return !areSame(*this, other);
}

bool lang::Signature::areSame(const lang::Signature& a, const lang::Signature& b)
{
    if (a.function_name_.text() != b.function_name_.text()) return false;
    return a.isSame(b.types_);
}
