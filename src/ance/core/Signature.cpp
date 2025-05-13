#include "Signature.h"

ance::core::Signature::Signature(Identifier const& name, size_t const arity) : name_(name), arity_(arity) {}

ance::core::Identifier const& ance::core::Signature::name() const
{
    return name_;
}

size_t ance::core::Signature::arity() const
{
    return arity_;
}

ance::core::Signature ance::core::Signature::like(std::string const& name, size_t arity)
{
    return { Identifier::like(name), arity };
}
