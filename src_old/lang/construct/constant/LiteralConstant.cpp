#include "LiteralConstant.h"

#include "lang/type/Type.h"

lang::LiteralConstant::LiteralConstant(lang::ResolvingHandle<lang::Type> type) : Constant(type), type_(std::move(type))
{}

lang::ResolvingHandle<lang::Type> lang::LiteralConstant::type()
{
    return type_;
}

lang::Type const& lang::LiteralConstant::type() const
{
    return *type_;
}

bool lang::LiteralConstant::validate(ValidationLogger&, lang::Location) const
{
    return true;
}
