#include "Provider.h"

#include <map>

#include "ance/core/Entity.h"

struct ance::cet::Provider::Implementation
{
    void insert(utility::Shared<core::Entity> entity)
    {
        entities.insert_or_assign(entity->name(), std::move(entity));
    }

    [[nodiscard]] core::Entity const* provide(core::Identifier const& identifier) const
    {
        auto const it = entities.find(identifier);
        if (it != entities.end()) return it->second.get();
        return nullptr;
    }

    std::map<core::Identifier, utility::Shared<core::Entity>> entities = {};
};

ance::cet::Provider::Provider() : implementation_(utility::makeOwned<Implementation>()) {}
ance::cet::Provider::~Provider() = default;

ance::utility::Owned<ance::cet::Provider> ance::cet::Provider::fromList(utility::List<utility::Shared<core::Entity>>&& entities)
{
    utility::Owned<Provider> provider = utility::makeOwned<Provider>();

    for (auto& entity : entities) { provider->implementation_->insert(std::move(entity)); }

    return provider;
}

ance::core::Entity const* ance::cet::Provider::provide(core::Identifier const& identifier) const
{
    return implementation_->provide(identifier);
}
