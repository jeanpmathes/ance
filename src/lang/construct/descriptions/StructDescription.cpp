#include "StructDescription.h"

#include "lang/ApplicationVisitor.h"
#include "lang/type/StructType.h"
#include "lang/type/VoidType.h"
#include "validation/Utilities.h"
#include "validation/ValidationLogger.h"

lang::StructDescription::StructDescription(lang::AccessModifier             access,
                                           lang::Identifier                 name,
                                           std::vector<Owned<lang::Member>> members,
                                           lang::Location                   definition_location)
    : access_(access)
    , name_(name)
    , members_(std::move(members))
    , definition_location_(definition_location)
{}

lang::Identifier const& lang::StructDescription::name() const
{
    return name_;
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
        makeOwned<lang::StructType>(access_, name_, members, definition_location_);
    type->define(std::move(struct_definition));

    self_ = type.handle();

    scope().getGlobalScope()->addType(std::move(type));
}

void lang::StructDescription::validate(ValidationLogger& validation_logger) const
{
    assert(self_.hasValue());
    lang::Type const& self = self_.value();

    if (access_ == lang::AccessModifier::EXTERN_ACCESS)
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

        if (type == lang::VoidType::get())
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

lang::Description::Descriptions lang::StructDescription::expand() const
{
    Descriptions result;

    std::vector<Owned<lang::Member>> members;
    members.reserve(members_.size());
    for (auto& member : members_) { members.emplace_back(member->expand()); }

    result.emplace_back(makeOwned<StructDescription>(access_, name_, std::move(members), definition_location_));

    return result;
}
