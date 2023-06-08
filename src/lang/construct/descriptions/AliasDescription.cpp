#include "AliasDescription.h"

#include "lang/ApplicationVisitor.h"
#include "lang/type/TypeAlias.h"
#include "lang/utility/Storage.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::AliasDescription::AliasDescription(lang::Accessibility               accessibility,
                                         lang::Identifier                  name,
                                         lang::ResolvingHandle<lang::Type> actual,
                                         lang::Location                    definition_location,
                                         lang::Location                    actual_type_location)
    : Description(accessibility)
    , name_(name)
    , actual_(std::move(actual))
    , definition_location_(definition_location)
    , actual_type_location_(actual_type_location)
{}

lang::AliasDescription::AliasDescription(bool from_public_import)
    : Description(lang::Accessibility::imported(from_public_import))
    , name_(lang::Identifier::empty())
    , actual_(lang::Type::getUndefined())
    , definition_location_(lang::Location::global())
    , actual_type_location_(lang::Location::global())
{}

lang::Identifier const& lang::AliasDescription::name() const
{
    return name_;
}

lang::Type const& lang::AliasDescription::actual() const
{
    return actual_;
}

bool lang::AliasDescription::isOverloadAllowed() const
{
    return false;
}

void lang::AliasDescription::performInitialization()
{
    lang::OwningHandle<lang::Type> type =
        lang::OwningHandle<lang::Type>::takeOwnership(lang::makeHandled<lang::Type>(name_));

    Owned<lang::TypeDefinition> alias_definition =
        makeOwned<lang::TypeAlias>(access(), name_, actual_, definition_location_);
    type->define(std::move(alias_definition));

    self_ = type.handle();

    scope().getGlobalScope()->addType(std::move(type));

    scope().addType(actual_);
}

void lang::AliasDescription::validate(ValidationLogger& validation_logger) const
{
    assert(self_.hasValue());
    lang::Type const& self = self_.value();

    if (access().modifier() == lang::AccessModifier::EXTERN_ACCESS)
    {
        validation_logger.logError("Aliases cannot be extern", definition_location_);
    }

    if (actual_->getDefinition() == self.getDefinition())
    {
        validation_logger.logError("Cannot alias self", actual_type_location_);
    }

    if (lang::validation::isTypeUndefined(actual_, &scope(), actual_type_location_, validation_logger)) return;

    if (access().modifier() == lang::AccessModifier::PUBLIC_ACCESS)
    {
        lang::validation::isTypeExportable(actual_, actual_type_location_, validation_logger);
    }

    self.getDefinition()->checkDependencies(validation_logger);

    actual_->validate(validation_logger, actual_type_location_);
}

lang::Description::Descriptions lang::AliasDescription::expand(lang::Context& new_context) const
{
    Descriptions result;

    result.emplace_back(makeOwned<AliasDescription>(access(),
                                                    name_,
                                                    actual_->createUndefinedClone(new_context),
                                                    definition_location_,
                                                    actual_type_location_));

    return result;
}

void lang::AliasDescription::sync(Storage& storage)
{
    storage.sync(name_);
    storage.sync(actual_);
}
