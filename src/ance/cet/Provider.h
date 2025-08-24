#ifndef PROVIDER_H
#define PROVIDER_H

#include "ance/core/Identifier.h"
#include "ance/utility/Owners.h"
#include "ance/utility/Containers.h"

namespace ance::core
{
    class Entity;
}

namespace ance::cet
{
    /// Provides entities to use during resolution.
    class Provider
    {
    public:
        Provider();
        ~Provider();

        static utility::Owned<Provider> fromList(utility::List<utility::Shared<core::Entity>>&& entities);

        /// Provides an entity for the given identifier, or nullptr if no such entity exists.
        [[nodiscard]] core::Entity const* provide(core::Identifier const& identifier) const;

    private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
