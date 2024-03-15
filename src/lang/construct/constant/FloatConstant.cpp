#include "FloatConstant.h"

#include <utility>

#include "compiler/CompileContext.h"
#include "lang/type/Type.h"

lang::FloatConstant::FloatConstant(std::string const&                number,
                                   llvm::fltSemantics const&         semantics,
                                   lang::ResolvingHandle<lang::Type> type)
    : LiteralConstant(type)
    , text_(number)
    , float_(semantics, number)
{}

std::string lang::FloatConstant::toString() const
{
    std::string suffix;

    if (type().isFloatingPointType(16)) suffix += "h";
    if (type().isFloatingPointType(32)) suffix += "s";
    if (type().isFloatingPointType(64)) suffix += "d";
    if (type().isFloatingPointType(128)) suffix += "q";

    return text_ + suffix;
}

Shared<lang::Constant> lang::FloatConstant::embed(CompileContext& context) const
{
    return context.exec().getFloatingPoint(float_, type());
}

bool lang::FloatConstant::equals(lang::Constant const* other) const
{
    auto other_float = dynamic_cast<FloatConstant const*>(other);
    if (!other_float) return false;

    return this->float_ == other_float->float_;
}

Shared<lang::LiteralConstant> lang::FloatConstant::clone(lang::Context& new_context) const
{
    return Shared<lang::LiteralConstant>(
        *(new FloatConstant(text_, float_.getSemantics(), type().getUndefinedTypeClone(new_context))));
}
