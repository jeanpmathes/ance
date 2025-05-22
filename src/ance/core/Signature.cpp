#include "Signature.h"

#include <utility>

ance::core::Signature::Signature(Identifier const& name, utility::List<std::reference_wrapper<Type const>> types)
    : name_(name), types_(std::move(types))
{

}

ance::core::Identifier const& ance::core::Signature::name() const
{
    return name_;
}

size_t ance::core::Signature::arity() const
{
    return types_.size();
}

ance::utility::List<std::reference_wrapper<ance::core::Type const>> const& ance::core::Signature::types() const
{
    return types_;
}
