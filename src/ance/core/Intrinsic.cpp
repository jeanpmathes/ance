#include "Intrinsic.h"

#include <utility>

#include "Type.h"

ance::core::Intrinsic::Intrinsic(Signature signature, Type const& return_type)
    : signature_(std::move(signature)), return_type_(return_type) {}

ance::core::Signature const& ance::core::Intrinsic::signature() const
{
    return signature_;
}

ance::core::Type const& ance::core::Intrinsic::returnType() const
{
    return return_type_;
}

ance::core::Identifier const& ance::core::Intrinsic::identifier() const
{
    return signature().name();
}

void ance::core::Intrinsic::display(std::ostream& os) const
{
    os << signature().name();
}

ance::core::Dynamic::Dynamic(Signature signature, Type const& return_type)
    : Intrinsic(std::move(signature), return_type)
{}

void ance::core::Dynamic::display(std::ostream& os) const
{
    os << "\"" << signature().name() << "\"";
}

ance::core::NoOp::NoOp() : Static(Signature::like("nop"), Type::Unit()) {}

ance::core::Declare::Declare() : Static(Signature::like("declare", Type::Ident(), Type::Self()), Type::EntityRef()) {}

ance::core::Resolve::Resolve() : Static(Signature::like("resolve", Type::Ident()), Type::EntityRef()) {}

std::ostream& operator<<(std::ostream& os, ance::core::Intrinsic const& intrinsic)
{
    intrinsic.display(os);
    return os;
}
