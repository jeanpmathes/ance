#include "Parameter.h"

#include <utility>

#include "lang/type/Type.h"
#include "lang/utility/Storage.h"
#include "lang/utility/Values.h"

lang::Parameter::Parameter(lang::ResolvingHandle<lang::Type> type,
                           lang::Location                    type_location,
                           Identifier                        name,
                           lang::Location                    location)
    : type_(std::move(type))
    , type_location_(type_location)
    , name_(name)
    , location_(location)
{}

lang::ResolvingHandle<lang::Type> lang::Parameter::type()
{
    return type_;
}

lang::Type const& lang::Parameter::type() const
{
    return type_;
}

lang::Identifier const& lang::Parameter::name() const
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
    if (!native_value_) { native_value_ = lang::values::contentToNative(type(), content_value_, context); }
}

void lang::Parameter::buildContentValue(CompileContext& context)
{
    if (!content_value_) { content_value_ = lang::values::nativeToContent(type(), native_value_, context); }
}

llvm::Value* lang::Parameter::getNativeValue() const
{
    return native_value_;
}

llvm::Value* lang::Parameter::getContentValue() const
{
    return content_value_;
}

Shared<lang::Parameter> lang::Parameter::expand(lang::Context& new_context) const
{
    return makeShared<lang::Parameter>(type_->createUndefinedClone(new_context), type_location_, name_, location_);
}

void lang::Parameter::synchronize(lang::Parameter* parameter, Storage& storage)
{
    storage.sync(parameter->name_);
    storage.sync(parameter->type_);
}
