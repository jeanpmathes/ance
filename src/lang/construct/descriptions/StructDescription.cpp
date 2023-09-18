#include "StructDescription.h"

#include "lang/ApplicationVisitor.h"
#include "lang/scope/StructScope.h"
#include "lang/type/StructType.h"
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
    , self_(lang::makeHandled<lang::Type>(name_))
{}

lang::StructDescription::StructDescription(bool from_public_import)
    : Description(lang::Accessibility::imported(from_public_import))
    , name_(lang::Identifier::empty())
    , members_()
    , definition_location_(lang::Location::global())
    , self_(lang::Type::getUndefined())
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

std::vector<std::reference_wrapper<const lang::Entity>> lang::StructDescription::getProvidedEntities() const
{
    return {std::cref(self_.base())};
}

std::vector<lang::Description::Dependency> lang::StructDescription::getDeclarationDependencies() const
{
    return {};
}

std::vector<lang::Description::Dependency> lang::StructDescription::getDefinitionDependencies() const
{
    std::vector<Dependency> dependencies;

    for (auto& dependency : struct_scope_.value()->getDependenciesOnDeclaration())
    {
        dependencies.emplace_back(dependency, false);
    }

    for (auto& dependency : struct_scope_.value()->getDependenciesOnDefinition())
    {
        dependencies.emplace_back(dependency);
    }

    return dependencies;
}

void lang::StructDescription::performInitialization()
{
    std::vector<std::reference_wrapper<lang::Member>> members;
    members.reserve(members_.size());
    for (auto& member : members_) { members.emplace_back(*member); }

    Owned<lang::TypeDefinition> struct_definition =
        makeOwned<lang::StructType>(access(), name_, members, definition_location_);
    self_->define(std::move(struct_definition));

    struct_scope_ = makeOwned<lang::StructScope>(scope(), self_);
    for (auto& member : members_) { member->setScope(getPtr(struct_scope_)); }
}

void lang::StructDescription::resolveDeclaration() {}

void lang::StructDescription::resolveDefinition()
{
    scope().addEntity(lang::OwningHandle<lang::Type>::takeOwnership(self_));

    struct_scope_.value()->resolve();
}

void lang::StructDescription::postResolve()
{
    struct_scope_.value()->postResolve();
}

void lang::StructDescription::validate(ValidationLogger& validation_logger) const
{
    if (access().modifier() == lang::AccessModifier::EXTERN_ACCESS)
    {
        validation_logger.logError("Structs cannot be extern", definition_location_);
    }

    bool valid = true;

    for (auto& member : members_)
    {
        auto const& type = member->type();

        if (type == self_)
        {
            validation_logger.logError("Cannot declare recursive member", member->location());
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

void lang::StructDescription::buildDeclaration(CompileContext& context)
{
    self_->buildNativeDeclaration(context);
}

void lang::StructDescription::buildDefinition(CompileContext& context)
{
    self_->buildNativeDefinition(context);
}

void lang::StructDescription::sync(Storage& storage)
{
    storage.sync(name_);

    if (storage.isReading()) { self_ = lang::makeHandled<lang::Type>(name_); }

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
