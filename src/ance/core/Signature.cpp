#include "Signature.h"

#include <utility>

ance::core::Signature::Parameter::Parameter(Identifier const& parameter_name, std::reference_wrapper<Type const> const parameter_type) : name(parameter_name), type(parameter_type) {}

ance::core::Signature::Signature(Identifier const& name, utility::List<Parameter> parameters)
    : name_(name), parameters_(std::move(parameters))
{
}

ance::core::Identifier const& ance::core::Signature::name() const
{
    return name_;
}

size_t ance::core::Signature::arity() const
{
    return parameters_.size();
}

ance::utility::List<ance::core::Signature::Parameter> const& ance::core::Signature::parameters() const
{
    return parameters_;
}
