#include "Scope.h"

#include "ance/utility/Containers.h"

#include "ance/core/Variable.h"

struct ance::core::Scope::Implementation
{
    Implementation() = default;

    utility::Owned<Scope> createChild(Scope& self)
    {
        utility::Owned<Scope> child = utility::makeOwned<Scope>();
        child->implementation_ = utility::makeOwned<Implementation>(&self);

        children_.emplace_back(*child);

        return child;
    }

    Variable const& addVariable(Identifier const& identifier, Type const& type, Location const& location)
    {
        return *variables_.emplace_back(utility::makeOwned<Variable>(identifier, type, location));
    }

    explicit Implementation(Scope* parent) : parent_(parent)
    {
        (void) parent_; // todo: use or remove
    }

private:
    Scope* parent_ = nullptr;

    utility::List<std::reference_wrapper<Scope>> children_ = {};
    utility::List<utility::Owned<Variable>> variables_ = {};
};

ance::core::Scope::Scope() : implementation_(utility::makeOwned<Implementation>(nullptr))
{

}

ance::core::Scope::~Scope() = default;

ance::utility::Owned<ance::core::Scope> ance::core::Scope::createChild()
{
    return implementation_->createChild(*this);
}

ance::core::Variable const& ance::core::Scope::addVariable(Identifier const& identifier, Type const& type, Location const& location)
{
    return implementation_->addVariable(identifier, type, location);
}
