#include "Scope.h"

#include "ance/cet/ValueExtensions.h"
#include "ance/cet/Temporary.h"

ance::cet::Scope::Scope(Scope* parent) : parent_(parent) {}

ance::cet::Scope* ance::cet::Scope::parent() const
{
    return parent_;
}

ance::utility::Optional<ance::utility::Shared<ance::bbt::Value>> ance::cet::Scope::declare(core::Identifier const& identifier,
                                                                                            core::Type const&       type,
                                                                                            bool                    is_final,
                                                                                            core::Location const&   location,
                                                                                            core::Reporter&         reporter)
{
    if (!canDeclare(identifier))
    {
        reporter.error("Declaring '" + identifier + "' in this scope would block previous access to outside of the scope", location);
        return std::nullopt;
    }

    utility::Owned<Variable> variable     = utility::makeOwned<Variable>(identifier, type, is_final, location);
    Variable&                variable_ref = *variable;

    onDeclare(std::move(variable));

    return VariableRefValue::make(variable_ref);
}

ance::utility::Optional<ance::utility::Shared<ance::bbt::Value>> ance::cet::Scope::find(
    core::Identifier const&                                                                        identifier,
    std::function<utility::Optional<utility::Shared<bbt::Value>>(core::Identifier const&)> const& provider)
{
    Variable * variable = onFind(identifier);

    if (variable != nullptr) { return VariableRefValue::make(*variable); }

    if (parent_ != nullptr) { return parent_->find(identifier, provider); }

    return provider(identifier);
}

ance::cet::Temporary& ance::cet::Scope::createTemporary(bbt::Temporary const& bbt_temporary)
{
    auto [iterator, inserted] = temporaries_.emplace(&bbt_temporary, utility::makeOwned<Temporary>());

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

ance::cet::OrderedScope::OrderedScope(Scope* parent) : Scope(parent) {}

bool ance::cet::OrderedScope::canDeclare(core::Identifier const& identifier) const
{
    return !outer_identifiers_.contains(identifier);
}

void ance::cet::OrderedScope::onDeclare(utility::Owned<Variable> variable)
{
    active_variables_.emplace(variable->name(), std::ref(*variable));
    all_variables_.emplace_back(std::move(variable));
}

ance::cet::Variable* ance::cet::OrderedScope::onFind(core::Identifier const& identifier)
{
    if (active_variables_.contains(identifier)) { return &active_variables_.at(identifier).get(); }

    outer_identifiers_.insert(identifier);

    return nullptr;
}

ance::cet::UnorderedScope::UnorderedScope(Scope* parent) : Scope(parent) {}

bool ance::cet::UnorderedScope::canDeclare(core::Identifier const& identifier) const
{
    return !variables_.contains(identifier);
}

void ance::cet::UnorderedScope::onDeclare(utility::Owned<Variable> variable)
{
    variables_.emplace(variable->name(), std::ref(*variable));
    all_variables_.emplace_back(std::move(variable));
}

ance::cet::Variable* ance::cet::UnorderedScope::onFind(core::Identifier const& identifier)
{
    if (variables_.contains(identifier)) { return &variables_.at(identifier).get(); }

    return nullptr;
}
