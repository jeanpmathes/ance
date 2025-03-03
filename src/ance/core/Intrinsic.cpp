#include "Intrinsic.h"

ance::core::Print const& ance::core::Intrinsic::print()
{
    static Print const instance;
    return instance;
}

ance::core::Dynamic::Dynamic(Identifier const& identifier)
        : identifier_(identifier)
{}

ance::core::Identifier const& ance::core::Dynamic::identifier() const
{
    return identifier_;
}

void ance::core::Dynamic::display(std::ostream& os) const
{
    os << "\"" << identifier_ << "\"";
}

std::ostream& operator<<(std::ostream& os, ance::core::Intrinsic const& intrinsic)
{
    intrinsic.display(os);
    return os;
}
