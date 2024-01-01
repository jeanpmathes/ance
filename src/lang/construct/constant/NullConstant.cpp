#include "NullConstant.h"

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/Context.h"
#include "lang/type/NullValueType.h"

lang::NullConstant::NullConstant(lang::Context& new_context) : type_(new_context.getNullValueType()) {}

std::string lang::NullConstant::toString() const
{
    return "null";
}

lang::ResolvingHandle<lang::Type> lang::NullConstant::type()
{
    return type_;
}

lang::Type const& lang::NullConstant::type() const
{
    return type_;
}

llvm::Constant* lang::NullConstant::createContent(CompileContext& context)
{
    return type_->getDefaultContent(context);
}

bool lang::NullConstant::equals(lang::Constant const* other) const
{
    auto* other_null = dynamic_cast<NullConstant const*>(other);
    return other_null != nullptr;
}

Shared<lang::Constant> lang::NullConstant::clone(lang::Context& new_context) const
{
    return create(new_context);
}

Shared<lang::NullConstant> lang::NullConstant::create(lang::Context& new_context)
{
    return makeShared<lang::NullConstant>(new_context);
}
