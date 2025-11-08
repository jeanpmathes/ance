#include "Provider.h"

#include <map>

#include "ance/bbt/Function.h"
#include "ance/utility/Optional.h"

struct ance::cet::Provider::Implementation
{
    void insert(utility::Shared<bbt::Function> function)
    {
        functions.insert_or_assign(function->name(), std::move(function));
    }

    [[nodiscard]] utility::Optional<utility::Shared<bbt::Function>> provide(core::Identifier const& identifier)
    {
        auto const it = functions.find(identifier);
        if (it != functions.end()) return it->second;
        return std::nullopt;
    }

    std::map<core::Identifier, utility::Shared<bbt::Function>> functions = {};
};

ance::cet::Provider::Provider() : implementation_(utility::makeOwned<Implementation>()) {}
ance::cet::Provider::~Provider() = default;

ance::utility::Owned<ance::cet::Provider> ance::cet::Provider::fromList(utility::List<utility::Shared<bbt::Function>>&& functions)
{
    utility::Owned<Provider> provider = utility::makeOwned<Provider>();

    for (auto& function : functions) { provider->implementation_->insert(std::move(function)); }

    return provider;
}

ance::utility::Optional<ance::utility::Shared<ance::bbt::Function>>
ance::cet::Provider::provide(core::Identifier const& identifier)
{
    return implementation_->provide(identifier);
}
