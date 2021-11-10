#include "Parameter.h"

#include <utility>

#include "ance/type/Type.h"
#include "ance/utility/Values.h"

ance::Parameter::Parameter(ance::ResolvingHandle<ance::Type> type, std::string name, ance::Location location)
    : type_(type)
    , name_(std::move(name))
    , location_(location)
{}

ance::ResolvingHandle<ance::Type> ance::Parameter::type()
{
    return type_;
}

std::string ance::Parameter::name()
{
    return name_;
}

ance::Location ance::Parameter::location() const
{
    return location_;
}

void ance::Parameter::wrap(llvm::Argument* argument)
{
    content_value_ = argument;
    content_value_->setName(name_ + ".arg");
}

void ance::Parameter::buildNativeValue(CompileContext* context)
{
    if (!native_value_) { native_value_ = ance::Values::contentToNative(type(), content_value_, context); }
}

void ance::Parameter::buildContentValue(CompileContext* context)
{
    if (!content_value_) { content_value_ = ance::Values::nativeToContent(type(), native_value_, context); }
}

llvm::Value* ance::Parameter::getNativeValue()
{
    return native_value_;
}

llvm::Value* ance::Parameter::getContentValue()
{
    return content_value_;
}
