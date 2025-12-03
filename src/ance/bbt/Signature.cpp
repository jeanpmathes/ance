#include "Signature.h"

#include <utility>

#include "ance/bbt/Type.h"

namespace ance::bbt
{
    Signature::Parameter::Parameter(core::Identifier const& parameter_name, utility::Shared<Type> parameter_type)
        : name(parameter_name)
        , type(std::move(parameter_type))
    {}

    Signature::Signature(core::Identifier const& name, utility::List<Parameter> parameters)
        : name_(name), parameters_(std::move(parameters))
    {}

    core::Identifier const& Signature::name() const
    {
        return name_;
    }

    size_t Signature::arity() const
    {
        return parameters_.size();
    }

    Signature::Parameter& Signature::operator[](size_t const index)
    {
        assert(index < parameters_.size());

        return parameters_[index];
    }

    utility::List<Signature::Parameter> const& Signature::parameters() const
    {
        return parameters_;
    }
}
