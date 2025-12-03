#include "Intrinsic.h"

#include <utility>

ance::core::Intrinsic::Intrinsic(Identifier const& identifier) : identifier_(identifier)
{

}
ance::core::Identifier const& ance::core::Intrinsic::identifier() const
{
    return identifier_;
}

void ance::core::Intrinsic::display(std::ostream& os) const
{
    os << identifier();
}
ance::core::Dynamic::Dynamic(Identifier const& identifier) : Intrinsic(identifier)
{

}

void ance::core::Dynamic::display(std::ostream& os) const
{
    os << "\"" << identifier() << "\"";
}

std::ostream& operator<<(std::ostream& os, ance::core::Intrinsic const& intrinsic)
{
    intrinsic.display(os);
    return os;
}
