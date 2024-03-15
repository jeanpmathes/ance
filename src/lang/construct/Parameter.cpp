#include "Parameter.h"

#include <utility>

#include "lang/type/Type.h"
#include "lang/utility/Storage.h"
#include "lang/construct/Variable.h"

lang::Parameter::Parameter(lang::ResolvingHandle<lang::Type> type,
                           lang::Location                    type_location,
                           Identifier                        name,
                           lang::Location                    location)
    : type_(nullptr)
    , type_opt_(std::move(type))
    , type_location_(type_location)
    , name_(name)
    , location_(location)
{}

lang::Parameter::Parameter(lang::ResolvingHandle<lang::Type> type)
    : type_(nullptr)
    , type_opt_(std::move(type))
    , type_location_(lang::Location::global())
    , name_(Identifier::empty())
    , location_(lang::Location::global())
{

}

lang::Parameter::Parameter(lang::Type const& type)
    : type_(&type)
    , type_opt_(std::nullopt)
    , type_location_(lang::Location::global())
    , name_(Identifier::empty())
    , location_(lang::Location::global())
{}

lang::ResolvingHandle<lang::Type> lang::Parameter::type()
{
    return type_opt_.value();
}

lang::Type const& lang::Parameter::type() const
{
    return type_ != nullptr ? *type_ : *type_opt_;
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

void lang::Parameter::argument(lang::ResolvingHandle<lang::Variable> variable)
{
    assert(!argument_.hasValue());

    argument_ = std::move(variable);
}

lang::ResolvingHandle<lang::Variable> lang::Parameter::argument()
{
    return *argument_;
}

lang::Variable const& lang::Parameter::argument() const
{
    return *argument_;
}

Shared<lang::Parameter> lang::Parameter::expand(lang::Context& new_context) const
{
    return makeShared<lang::Parameter>(type_opt_.value()->getUndefinedTypeClone(new_context), type_location_, name_, location_);
}

void lang::Parameter::synchronize(lang::Parameter* parameter, Storage& storage)
{
    lang::ResolvingHandle<lang::Type> type = *parameter->type_opt_;

    storage.sync(parameter->name_);
    storage.sync(type);

    parameter->type_opt_ = type;
}
