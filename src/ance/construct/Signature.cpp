#include "Signature.h"

ance::Signature::Signature(const std::string& name, std::vector<ance::ResolvingHandle<ance::Type>>& types)
    : function_name_(name)
    , types_(types)
{}

size_t ance::Signature::getParameterCount() const
{
    return types_.size();
}

ance::Signature ance::Signature::fromParameters(const std::string&                                   name,
                                                const std::vector<std::shared_ptr<ance::Parameter>>& parameters)
{
    std::vector<ResolvingHandle<Type>> types;

    types.reserve(parameters.size());
    for (auto& parameter : parameters) { types.push_back(parameter->type()); }

    return Signature(name, types);
}

bool ance::Signature::isMatching(const std::vector<ance::ResolvingHandle<ance::Type>>& arguments) const
{
    if (types_.size() != arguments.size()) return false;

    auto types = llvm::zip(types_, arguments);
    return std::all_of(types.begin(), types.end(), [](const auto& pair) {
        return ance::Type::isMatching(std::get<0>(pair), std::get<1>(pair));
    });
}

const std::string& ance::Signature::getMangledName()
{
    if (!mangled_name_.empty()) return mangled_name_;

    mangled_name_ = function_name_ + "$$overload(";

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

std::string ance::Signature::toString() const
{
    std::string string = function_name_ + " (";

    bool is_first = true;
    for (auto& type : types_)
    {
        if (!is_first) { string += ", "; }

        is_first = false;
        string += type->getActualType()->getName();
    }

    string += ")";
    return string;
}

bool ance::Signature::operator==(const ance::Signature& other) const
{
    return areSame(*this, other);
}

bool ance::Signature::operator!=(const ance::Signature& other) const
{
    return !areSame(*this, other);
}

bool ance::Signature::areSame(const ance::Signature& a, const ance::Signature& b)
{
    if (a.function_name_ != b.function_name_) return false;
    if (a.types_.size() != b.types_.size()) return false;

    auto types = llvm::zip(a.types_, b.types_);
    return std::all_of(types.begin(), types.end(), [](const auto& pair) {
        return ance::Type::areSame(std::get<0>(pair), std::get<1>(pair));
    });
}
