#include "Variable.h"

ance::cet::Variable::Variable(core::Identifier const& identifier, core::Type const& type, bool is_final, core::Location const& location)
    : identifier_(identifier)
    , type_(type)
    , variable_(identifier, type, is_final, location)
{}

ance::core::Identifier const& ance::cet::Variable::identifier() const
{
    return identifier_;
}

ance::core::Type const& ance::cet::Variable::type() const
{
    return type_;
}

ance::core::Variable const& ance::cet::Variable::variable() const
{
    return variable_;
}
