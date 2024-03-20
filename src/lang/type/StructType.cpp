#include "StructType.h"

#include <llvm/IR/Constant.h>

#include "compiler/CompileContext.h"
#include "lang/ApplicationVisitor.h"
#include "lang/construct/Value.h"
#include "lang/scope/Scope.h"
#include "validation/ValidationLogger.h"

lang::StructType::StructType(lang::Accessibility                               accessibility,
                             lang::Identifier                                  name,
                             std::vector<std::reference_wrapper<lang::Member>> members,
                             lang::Location                                    location)
    : TypeDefinition(name, location)
    , CustomType(accessibility)
    , members_(std::move(members))
{

    for (auto& member : members_)
    {
        member_map_.emplace(member.get().name(), member);
        member.get().setIndex(member_map_.size() - 1);
    }
}

StateCount lang::StructType::getStateCount() const
{
    StateCount state_count = StateCount::unit();

    for (auto& member : members_) { state_count = state_count * member.get().type()->getStateCount(); }

    return state_count;
}

bool lang::StructType::isStructType() const
{
    return true;
}

std::string lang::StructType::createMangledName() const
{
    return "struct(" + name() + ")";
}

void lang::StructType::registerExecutionType(CompileContext& context) const
{
    context.exec().createStruct(self(), members_, getDefinitionLocation());
}

std::vector<lang::ResolvingHandle<lang::Type>> lang::StructType::getDeclarationDependencies()
{
    std::vector<lang::ResolvingHandle<lang::Type>> dependencies;
    std::set<lang::Identifier>                     added;

    for (auto& member : members_)
    {
        auto type = member.get().type();

        if (!added.contains(type->name()))
        {
            dependencies.emplace_back(type);
            added.insert(type->name());
        }
    }

    return dependencies;
}

std::vector<lang::ResolvingHandle<lang::Type>> lang::StructType::getDefinitionDependencies()
{
    return {};
}

bool lang::StructType::hasMember(lang::Identifier const& name) const
{
    return member_map_.contains(name);
}

lang::Member& lang::StructType::getMember(lang::Identifier const& name)
{
    if (member_map_.contains(name)) { return member_map_.at(name); }

    return TypeDefinition::getMember(name);
}

lang::Member const& lang::StructType::getMember(lang::Identifier const& name) const
{
    if (member_map_.contains(name)) { return member_map_.at(name); }

    return TypeDefinition::getMember(name);
}

bool lang::StructType::validateMemberAccess(lang::Identifier const& name, ValidationLogger& validation_logger) const
{
    if (member_map_.at(name).get().access() == AccessModifier::PRIVATE_ACCESS)
    {
        validation_logger.logError("Cannot access private member '" + name + "'", name.location());
        return false;
    }

    return true;
}

Shared<lang::Value> lang::StructType::buildMemberAccess(Shared<lang::Value>     value,
                                                        lang::Identifier const& name,
                                                        CompileContext&         context) const
{
    Shared<lang::Value> struct_ptr = context.exec().computeAddressOf(value);
    Shared<lang::Value> member_ptr = context.exec().computeMemberPointer(struct_ptr, name);

    return context.exec().computeReferenceFromPointer(member_ptr);
}

void lang::StructType::performSingleDefaultInitializerDefinition(Shared<lang::Value> ptr, CompileContext& context) const
{
    for (auto member : members_)
    {
        Shared<lang::Value> member_ptr = context.exec().computeMemberPointer(ptr, member.get().name());
        member.get().buildInitialization(member_ptr, context);
    }
}

void lang::StructType::performSingleCopyInitializerDefinition(Shared<lang::Value> dts_ptr,
                                                              Shared<lang::Value> src_ptr,
                                                              CompileContext&     context) const
{
    for (auto member : members_)
    {
        Shared<lang::Value> dst_member_ptr = context.exec().computeMemberPointer(dts_ptr, member.get().name());
        Shared<lang::Value> src_member_ptr = context.exec().computeMemberPointer(src_ptr, member.get().name());
        member.get().type()->performCopyInitializer(dst_member_ptr, src_member_ptr, context);
    }
}

void lang::StructType::buildSingleDefaultFinalizerDefinition(Shared<lang::Value> ptr, CompileContext& context) const
{
    for (auto member : members_)
    {
        Shared<lang::Value> member_ptr = context.exec().computeMemberPointer(ptr, member.get().name());
        member.get().type()->performFinalizer(member_ptr, context);
    }
}
