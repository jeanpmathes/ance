#include "Scope.h"

#include "ance/bbt/Function.h"
#include "ance/bbt/Type.h"

#include "ance/cet/Provider.h"
#include "ance/cet/Temporary.h"
#include "ance/cet/ValueExtensions.h"

ance::cet::Scope::Scope(Scope* parent, bbt::TypeContext& type_context) : parent_(parent), type_context_(type_context) {}

ance::cet::Scope* ance::cet::Scope::parent() const
{
    return parent_;
}

ance::utility::Optional<ance::utility::Shared<ance::bbt::Value>> ance::cet::Scope::declare(core::Identifier const&    identifier,
                                                                                           utility::Shared<bbt::Type> type,
                                                                                           bool                       is_final,
                                                                                           core::Location const&      location,
                                                                                           core::Reporter&            reporter)
{
    if (!canDeclare(identifier))
    {
        reporter.error("Declaring '" + identifier + "' in this scope would block previous access to outside of the scope", location);
        return std::nullopt;
    }

    utility::Owned<Variable> variable     = utility::makeOwned<Variable>(identifier, type, is_final, location, type_context_);
    Variable&                variable_ref = *variable;

    onDeclare(std::move(variable));

    return VariableRef::make(variable_ref, type_context_);
}

ance::utility::Optional<ance::utility::Shared<ance::bbt::Value>> ance::cet::Scope::find(core::Identifier const& identifier)
{
    Variable* variable = onFind(identifier);

    if (variable != nullptr)
    {
        return VariableRef::make(*variable, type_context_);
    }

    if (parent_ != nullptr)
    {
        return parent_->find(identifier);
    }

    return std::nullopt;
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

ance::bbt::TypeContext& ance::cet::Scope::types()
{
    return type_context_;
}

ance::cet::GlobalScope::GlobalScope(utility::List<utility::Owned<Provider>>& providers, bbt::TypeContext& type_context)
    : Scope(nullptr, type_context)
    , providers_(providers)
{
    auto add_type_variable = [&](utility::Shared<bbt::Type> type) {
        variables_.emplace(type->name(), Variable::createConstant(type->name(), type, type_context));
    };

    add_type_variable(type_context.getBool());
    add_type_variable(type_context.getUnit());
    add_type_variable(type_context.getSize());
    add_type_variable(type_context.getString());
    add_type_variable(type_context.getIdentifier());
    add_type_variable(type_context.getType());
    add_type_variable(type_context.getLocation());
    add_type_variable(type_context.getFunction());
}

bool ance::cet::GlobalScope::canDeclare(core::Identifier const&) const
{
    return false;
}

void ance::cet::GlobalScope::onDeclare(utility::Owned<Variable>)
{
    assert(false);
}

ance::cet::Variable* ance::cet::GlobalScope::onFind(core::Identifier const& identifier)
{
    auto iterator = variables_.find(identifier);
    if (iterator != variables_.end())
    {
        auto& [_, variable] = *iterator;
        return variable.get();
    }

    for (auto& provider : this->providers_)
    {
        utility::Optional<utility::Shared<bbt::Function>> provided = provider->provide(identifier);
        if (provided.hasValue())
        {
            auto variable = utility::makeShared<Variable>(identifier, types().getFunction(), true, core::Location::global(), types());
            variables_.emplace(identifier, variable);

            variable->write(*provided);

            return variable.get();
        }
    }

    return nullptr;
}

ance::cet::OrderedScope::OrderedScope(Scope& parent, bbt::TypeContext& type_context) : Scope(&parent, type_context) {}

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
    if (active_variables_.contains(identifier))
    {
        return &active_variables_.at(identifier).get();
    }

    outer_identifiers_.insert(identifier);

    return nullptr;
}

ance::cet::UnorderedScope::UnorderedScope(Scope& parent, bbt::TypeContext& type_context) : Scope(&parent, type_context) {}

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
    if (variables_.contains(identifier))
    {
        return &variables_.at(identifier).get();
    }

    return nullptr;
}
