#include "Parameter.h"

#include <utility>

#include "lang/type/Type.h"
#include "lang/utility/Values.h"

lang::Parameter::Parameter(lang::ResolvingHandle<lang::Type> type,
                           lang::Location                    type_location,
                           Identifier                        name,
                           lang::Location                    location)
    : type_(type)
    , type_location_(type_location)
    , name_(std::move(name))
    , location_(location)
{}

lang::ResolvingHandle<lang::Type> lang::Parameter::type() const
{
    return type_;
}

lang::Identifier const& lang::Parameter::name()
{
    return name_;
}

lang::Location lang::Parameter::location() const
{
    return location_;
}

lang::Location lang::Parameter::typeLocation() const
{
    return type_location_;
}

void lang::Parameter::wrap(llvm::Argument* argument)
{
    content_value_ = argument;
    content_value_->setName(name_ + ".arg");
}

void lang::Parameter::buildNativeValue(CompileContext& context)
{
    if (!native_value_) { native_value_ = lang::Values::contentToNative(type(), content_value_, context); }
}

void lang::Parameter::buildContentValue(CompileContext& context)
{
    if (!content_value_) { content_value_ = lang::Values::nativeToContent(type(), native_value_, context); }
}

llvm::Value* lang::Parameter::getNativeValue()
{
    return native_value_;
}

llvm::Value* lang::Parameter::getContentValue()
{
    return content_value_;
}
