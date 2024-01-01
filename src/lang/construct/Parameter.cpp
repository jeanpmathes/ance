#include "Parameter.h"

#include <utility>

#include "lang/type/Type.h"
#include "lang/utility/Storage.h"

lang::Parameter::Parameter(lang::ResolvingHandle<lang::Type> type,
                           lang::Location                    type_location,
                           Identifier                        name,
                           lang::Location                    location)
    : type_(std::move(type))
    , type_location_(type_location)
    , name_(name)
    , location_(location)
{}

lang::Parameter::Parameter(lang::ResolvingHandle<lang::Type> type)
    : type_(std::move(type))
    , type_location_(lang::Location::global())
    , name_(Identifier::empty())
    , location_(lang::Location::global())
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
    argument_ = argument;

    if (!name_.isEmpty()) { argument_->setName(name_ + ".arg"); }
}

void lang::Parameter::buildContentValue(CompileContext&)
{
    content_value_ = argument_;
}

Shared<lang::Parameter> lang::Parameter::expand(lang::Context& new_context) const
{
    return makeShared<lang::Parameter>(type_->getUndefinedTypeClone(new_context), type_location_, name_, location_);
}

void lang::Parameter::synchronize(lang::Parameter* parameter, Storage& storage)
{
    storage.sync(parameter->name_);
    storage.sync(parameter->type_);
}
