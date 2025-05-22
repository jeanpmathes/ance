#include "Intrinsic.h"

#include "Type.h"

ance::core::Intrinsic::Intrinsic(Signature const& signature) : signature_(signature) {}

ance::core::Signature const& ance::core::Intrinsic::signature() const
{
    return signature_;
}

ance::core::Type const& ance::core::Intrinsic::returnType() const
{
    return Type::Unit();
}

ance::core::Dynamic::Dynamic(Signature const& signature)
    : Intrinsic(signature)
{}
ance::core::Identifier const& ance::core::Dynamic::identifier() const
{
    return signature().name();
}

void ance::core::Dynamic::display(std::ostream& os) const
{
    os << "\"" << signature().name() << "\"";
}

std::ostream& operator<<(std::ostream& os, ance::core::Intrinsic const& intrinsic)
{
    intrinsic.display(os);
    return os;
}
