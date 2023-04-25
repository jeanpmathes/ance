#include "StructDescription.h"

#include "lang/ApplicationVisitor.h"
#include "lang/type/StructType.h"
#include "lang/type/VoidType.h"
#include "lang/utility/Storage.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::StructDescription::StructDescription(lang::Accessibility              accessibility,
                                           lang::Identifier                 name,
                                           std::vector<Owned<lang::Member>> members,
                                           lang::Location                   definition_location)
    : Description(accessibility)
    , name_(name)
    , members_(std::move(members))
    , definition_location_(definition_location)
{}

lang::StructDescription::StructDescription(bool from_public_import)
    : Description(lang::Accessibility::imported(from_public_import))
    , name_(lang::Identifier::empty())
    , members_()
    , definition_location_(lang::Location::global())
{}

lang::Identifier const& lang::StructDescription::name() const
{
    return name_;
}

std::vector<std::reference_wrapper<const lang::Member>> lang::StructDescription::members() const
{
    std::vector<std::reference_wrapper<const lang::Member>> members;
    members.reserve(members_.size());
    for (auto& member : members_) { members.emplace_back(*member); }
    return members;
}

bool lang::StructDescription::isOverloadAllowed() const
{
    return false;
}

void lang::StructDescription::performInitialization()
{
    lang::OwningHandle<lang::Type> type =
        lang::OwningHandle<lang::Type>::takeOwnership(lang::makeHandled<lang::Type>(name_));

    std::vector<std::reference_wrapper<lang::Member>> members;
    members.reserve(members_.size());
    for (auto& member : members_) { members.emplace_back(*member); }

    Owned<lang::TypeDefinition> struct_definition =
        makeOwned<lang::StructType>(access(), name_, members, definition_location_);
    type->define(std::move(struct_definition));

    self_ = type.handle();

    scope().getGlobalScope()->addType(std::move(type));

    for (auto& member : members_) { member->setScope(&scope()); }
}

void lang::StructDescription::validate(ValidationLogger& validation_logger) const
{
    assert(self_.hasValue());
    lang::Type const& self = self_.value();

    if (access().modifier() == lang::AccessModifier::EXTERN_ACCESS)
    {
        validation_logger.logError("Structs cannot be extern", definition_location_);
    }

    bool valid = true;

    for (auto& member : members_)
    {
        auto const& type = member->type();

        if (!type.isDefined())
        {
            valid = not lang::validation::isTypeUndefined(type, member->location(), validation_logger);
            continue;
        }

        if (type == self)
        {
            validation_logger.logError("Cannot declare recursive member", member->location());
            valid = false;
            continue;
        }

        if (type == scope().context().getVoidType())
        {
            validation_logger.logError("Cannot declare member of 'void' type", member->location());
            valid = false;
            continue;
        }

        if (type.isReferenceType())
        {
            validation_logger.logError("Cannot declare member of reference type", member->location());
            valid = false;
            continue;
        }

        if (access().modifier() == lang::AccessModifier::PUBLIC_ACCESS
            && member->access() == lang::AccessModifier::PUBLIC_ACCESS)
        {
            lang::validation::isTypeExportable(type, member->location(), validation_logger);
        }
    }

    valid = valid && self.getDefinition()->checkDependencies(validation_logger);

    if (!valid) return;// These checks depend on the definition being roughly valid.

    std::set<lang::Identifier> member_names;

    for (auto& member : members_)
    {
        valid &= member->validate(validation_logger);

        if (member_names.contains(member->name()))
        {
            validation_logger.logError("Member name '" + member->name() + "' already used", member->name().location());
            valid = false;
        }

        member_names.insert(member->name());
    }
}

lang::Description::Descriptions lang::StructDescription::expand(lang::Context& new_context) const
{
    Descriptions result;

    std::vector<Owned<lang::Member>> members;
    members.reserve(members_.size());
    for (auto& member : members_) { members.emplace_back(member->expand(new_context)); }

    result.emplace_back(makeOwned<StructDescription>(access(), name_, std::move(members), definition_location_));

    return result;
}

void lang::StructDescription::sync(Storage& storage)
{
    storage.sync(name_);

    std::vector<Owned<lang::Member>> members = std::move(members_);
    members_.clear();

    uint64_t size = members.size();
    storage.sync(size);

    for (uint64_t i = 0; i < size; ++i)
    {
        if (storage.isReading())
        {
            members_.emplace_back(makeOwned<lang::Member>(lang::AccessModifier::PUBLIC_ACCESS,
                                                          lang::Identifier::empty(),
                                                          lang::Type::getUndefined(),
                                                          lang::Assigner::UNSPECIFIED,
                                                          std::nullopt,
                                                          lang::Location::global(),
                                                          lang::Location::global()));
        }

        if (storage.isWriting()) { members_.emplace_back(std::move(members[i])); }

        storage.sync(*members_.back());
    }
}
