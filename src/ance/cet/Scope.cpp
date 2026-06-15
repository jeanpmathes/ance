#include "Scope.h"

#include "ance/bbt/Function.h"
#include "ance/bbt/Type.h"

#include "ance/cet/Temporary.h"
#include "ance/cet/ValueExtensions.h"

ance::cet::FindResult ance::cet::FindResult::found(utility::Shared<bbt::Value> value)
{
    return {std::move(value), Status::FOUND, NotFound {}};
}

ance::cet::FindResult ance::cet::FindResult::notFound()
{
    return {std::nullopt, Status::NOT_FOUND, NotFound {}};
}

ance::cet::FindResult ance::cet::FindResult::erased(core::Location const& location)
{
    return {std::nullopt, Status::ERASED, Erased {location}};
}

ance::cet::Scope::Scope(Scope* parent, bbt::TypeContext& type_context) : parent_(parent), type_context_(type_context) {}

ance::cet::Scope* ance::cet::Scope::parent() const
{
    return parent_;
}

ance::utility::Optional<ance::utility::Shared<ance::bbt::Value>> ance::cet::Scope::declare(core::Identifier const&    identifier,
                                                                                           utility::Shared<bbt::Type> type,
                                                                                           bool                       is_variable,
                                                                                           core::Location const&      location,
                                                                                           core::Reporter&            reporter)
{
    DeclarationCheckResult check = canDeclare(identifier);

    if (check == DeclarationCheckResult::BLOCKS_OUTER)
    {
        reporter.error(location) << "Declaring " << identifier << " in this scope would block previous access to it outside of the scope";
        return std::nullopt;
    }

    if (check == DeclarationCheckResult::ALREADY_DEFINED)
    {
        reporter.error(location) << "Identifier " << identifier << " is already defined in this scope";
        return std::nullopt;
    }

    utility::Owned<Variable> variable     = utility::makeOwned<Variable>(identifier, type, is_variable, location, type_context_);
    Variable&                variable_ref = *variable;

    onDeclare(std::move(variable));

    return VariableRef::make(variable_ref, type_context_);
}

ance::cet::FindResult ance::cet::Scope::find(core::Identifier const& identifier)
{
    FindResult local = onFind(identifier);

    if (local.status == FindResult::Status::FOUND) return local;

    if (parent_ != nullptr)
    {
        FindResult from_parent = parent_->find(identifier);

        if (from_parent.status == FindResult::Status::FOUND) return from_parent;

        // In the case that it is not found in the parent scope, we do not want to lose the local erase information.
        if (local.status == FindResult::Status::ERASED) return local;

        return from_parent;
    }

    return local;
}

ance::cet::EraseResult ance::cet::Scope::erase(core::Identifier const& identifier)
{
    if (!isOrdered()) return EraseResult::IS_NOT_ORDERED;

    if (onErase(identifier)) return EraseResult::OK;

    Scope* current_scope = parent_;
    while (current_scope != nullptr)
    {
        if (current_scope->onContains(identifier)) return EraseResult::IS_OUTER;

        current_scope = current_scope->parent();
    }

    return EraseResult::NOT_FOUND;
}

ance::cet::Temporary& ance::cet::Scope::createTemporary(bbt::Temporary const& bbt_temporary)
{
    auto [iterator, inserted] = temporaries_.emplace(&bbt_temporary, utility::makeOwned<Temporary>(type_context_));

    assert(inserted);

    return *iterator->second;
}

ance::cet::Temporary& ance::cet::Scope::getTemporary(bbt::Temporary const& bbt_temporary)
{
    Scope* current_scope = this;

    while (current_scope != nullptr && !current_scope->temporaries_.contains(&bbt_temporary))
    {
        current_scope = current_scope->parent();
    }

    assert(current_scope != nullptr);

    return *current_scope->temporaries_.at(&bbt_temporary);
}

ance::cet::Scope& ance::cet::Scope::addChildScope(utility::Owned<Scope> child_scope)
{
    assert(child_scope->parent() == this);

    child_scopes_.emplace_back(std::move(child_scope));
    return *child_scopes_.back();
}

void ance::cet::Scope::removeChildScope(Scope& scope)
{
    auto const iterator = std::ranges::find_if(child_scopes_, [&scope](utility::Owned<Scope> const& s) { return s.get() == &scope; });
    assert(iterator != child_scopes_.end());

    child_scopes_.erase(iterator);
}

bool ance::cet::Scope::onErase(core::Identifier const&)
{
    return false;
}

bool ance::cet::Scope::isOrdered() const
{
    return false;
}

ance::bbt::TypeContext& ance::cet::Scope::types()
{
    return type_context_;
}

ance::cet::CoreScope::CoreScope(bbt::TypeContext& type_context) : Scope(nullptr, type_context) {}

ance::cet::DeclarationCheckResult ance::cet::CoreScope::canDeclare(core::Identifier const& identifier) const
{
    return variables_.contains(identifier) ? DeclarationCheckResult::ALREADY_DEFINED : DeclarationCheckResult::OK;
}

void ance::cet::CoreScope::onDeclare(utility::Owned<Variable> variable)
{
    variables_.emplace(variable->name(), std::move(variable));
}

ance::cet::FindResult ance::cet::CoreScope::onFind(core::Identifier const& identifier)
{
    auto const iterator = variables_.find(identifier);
    if (iterator != variables_.end()) return FindResult::found(VariableRef::make(*iterator->second, types()));

    return FindResult::notFound();
}

bool ance::cet::CoreScope::onContains(core::Identifier const& identifier) const
{
    return variables_.contains(identifier);
}

ance::cet::OrderedScope::OrderedScope(Scope& parent, bbt::TypeContext& type_context) : Scope(&parent, type_context) {}

ance::cet::DeclarationCheckResult ance::cet::OrderedScope::canDeclare(core::Identifier const& identifier) const
{
    return outer_identifiers_.contains(identifier) ? DeclarationCheckResult::BLOCKS_OUTER : DeclarationCheckResult::OK;
}

void ance::cet::OrderedScope::onDeclare(utility::Owned<Variable> variable)
{
    active_variables_.insert_or_assign(variable->name(), std::ref(*variable));
    all_variables_.emplace_back(std::move(variable));
}

ance::cet::FindResult ance::cet::OrderedScope::onFind(core::Identifier const& identifier)
{
    if (active_variables_.contains(identifier)) return FindResult::found(VariableRef::make(active_variables_.at(identifier).get(), types()));

    if (erased_variables_.contains(identifier)) return FindResult::erased(erased_variables_.at(identifier));

    outer_identifiers_.insert(identifier);
    return FindResult::notFound();
}

bool ance::cet::OrderedScope::onContains(core::Identifier const& identifier) const
{
    return active_variables_.contains(identifier);
}

bool ance::cet::OrderedScope::onErase(core::Identifier const& identifier)
{
    if (active_variables_.contains(identifier))
    {
        erased_variables_.emplace(identifier, identifier.location());
        active_variables_.erase(identifier);
        return true;
    }

    return false;
}

bool ance::cet::OrderedScope::isOrdered() const
{
    return true;
}

ance::cet::UnorderedScope::UnorderedScope(Scope& parent, bbt::TypeContext& type_context) : Scope(&parent, type_context) {}

ance::cet::DeclarationCheckResult ance::cet::UnorderedScope::canDeclare(core::Identifier const& identifier) const
{
    return variables_.contains(identifier) ? DeclarationCheckResult::ALREADY_DEFINED : DeclarationCheckResult::OK;
}

void ance::cet::UnorderedScope::onDeclare(utility::Owned<Variable> variable)
{
    variables_.emplace(variable->name(), std::ref(*variable));
    all_variables_.emplace_back(std::move(variable));
}

ance::cet::FindResult ance::cet::UnorderedScope::onFind(core::Identifier const& identifier)
{
    if (variables_.contains(identifier)) return FindResult::found(VariableRef::make(variables_.at(identifier).get(), types()));

    return FindResult::notFound();
}

bool ance::cet::UnorderedScope::onContains(core::Identifier const& identifier) const
{
    return variables_.contains(identifier);
}
