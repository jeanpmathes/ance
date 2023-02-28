#include "AliasDescription.h"

#include "lang/ApplicationVisitor.h"
#include "lang/type/TypeAlias.h"
#include "lang/type/VoidType.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::AliasDescription::AliasDescription(lang::AccessModifier              access,
                                         lang::Identifier                  name,
                                         lang::ResolvingHandle<lang::Type> actual,
                                         lang::Location                    definition_location,
                                         lang::Location                    actual_type_location)
    : access_(access)
    , name_(name)
    , actual_(std::move(actual))
    , definition_location_(definition_location)
    , actual_type_location_(actual_type_location)
{}

lang::Identifier const& lang::AliasDescription::name() const
{
    return name_;
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
        makeOwned<lang::TypeAlias>(name_, actual_, definition_location_, actual_type_location_);
    type->define(std::move(alias_definition));

    self_ = type.handle();

    scope().getGlobalScope()->addType(std::move(type));
}

void lang::AliasDescription::validate(ValidationLogger& validation_logger) const
{
    assert(self_.hasValue());
    lang::Type const& self = self_.value();

    if (access_ == lang::AccessModifier::EXTERN_ACCESS)
    {
        validation_logger.logError("Aliases cannot be extern", definition_location_);
    }

    if (actual_->getDefinition() == self.getDefinition())
    {
        validation_logger.logError("Cannot alias self", actual_type_location_);
    }

    lang::validation::isTypeUndefined(actual_, actual_type_location_, validation_logger);

    if (actual_ == lang::VoidType::get())// Prevent infinite recursion.
    {
        validation_logger.logError("Cannot create alias for 'void' type", definition_location_);
    }

    self.getDefinition()->checkDependencies(validation_logger);

    actual_->validate(validation_logger, actual_type_location_);
}

lang::Description::Descriptions lang::AliasDescription::expand() const
{
    Descriptions result;

    result.emplace_back(makeOwned<AliasDescription>(access_,
                                                    name_,
                                                    actual_->createUndefinedClone(),
                                                    definition_location_,
                                                    actual_type_location_));

    return result;
}
