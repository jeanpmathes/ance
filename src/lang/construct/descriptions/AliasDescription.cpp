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
    , self_(lang::makeHandled<lang::Type>(name_))
{}

lang::AliasDescription::AliasDescription(bool from_public_import)
    : Description(lang::Accessibility::imported(from_public_import))
    , name_(lang::Identifier::empty())
    , actual_(lang::Type::getUndefined())
    , definition_location_(lang::Location::global())
    , actual_type_location_(lang::Location::global())
    , self_(lang::Type::getUndefined())
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

lang::Type const& lang::AliasDescription::type() const
{
    return self_;
}

std::vector<std::reference_wrapper<const lang::Entity>> lang::AliasDescription::getProvidedEntities() const
{
    return {std::cref(self_.base())};
}

std::vector<lang::Description::Dependency> lang::AliasDescription::getDeclarationDependencies() const
{
    return {};
}

std::vector<lang::Description::Dependency> lang::AliasDescription::getDefinitionDependencies() const
{
    auto* self = const_cast<AliasDescription*>(this);

    std::vector<Dependency> result;

    if (auto type = self->actual_.as<lang::Type>(); type.hasValue())
    {
        auto declaration_dependencies = (**type).getDeclarationDependencies();
        for (auto& dependency : declaration_dependencies) { result.emplace_back(dependency, false); }
        auto definition_dependencies = (**type).getDefinitionDependencies();
        for (auto& dependency : definition_dependencies) { result.emplace_back(dependency); }

        if (declaration_dependencies.size() + definition_dependencies.size() == 0)
        {
            result.emplace_back(std::cref(*self->actual_));
        }
    }
    else { result.emplace_back(std::cref(*self->actual_)); }

    return result;
}

void lang::AliasDescription::performInitialization()
{
    Owned<lang::TypeDefinition> alias_definition =
        makeOwned<lang::TypeAlias>(access(), name_, actual_, definition_location_);
    self_->define(std::move(alias_definition));

    scope().registerUsage(actual_);
}

void lang::AliasDescription::resolveDeclaration() {}

void lang::AliasDescription::resolveDefinition()
{
    scope().addEntity(OwningHandle<lang::Type>::takeOwnership(self_));
}

void lang::AliasDescription::validate(ValidationLogger& validation_logger) const
{
    if (access().modifier() == lang::AccessModifier::EXTERN_ACCESS)
    {
        validation_logger.logError("Aliases cannot be extern", definition_location_);
    }

    if (actual_->getDefinition() == self_->getDefinition())
    {
        validation_logger.logError("Cannot alias self", actual_type_location_);
    }

    if (access().modifier() == lang::AccessModifier::PUBLIC_ACCESS)
    {
        lang::validation::isTypeExportable(actual_, actual_type_location_, validation_logger);
    }

    actual_->validate(validation_logger, actual_type_location_);
}

lang::Description::Descriptions lang::AliasDescription::expand(lang::Context& new_context) const
{
    Descriptions result;

    result.emplace_back(makeOwned<AliasDescription>(access(),
                                                    name_,
                                                    actual_->getUndefinedTypeClone(new_context),
                                                    definition_location_,
                                                    actual_type_location_));

    return result;
}

void lang::AliasDescription::sync(Storage& storage)
{
    storage.sync(name_);
    storage.sync(actual_);

    if (storage.isReading()) { self_ = lang::makeHandled<lang::Type>(name_); }
}
