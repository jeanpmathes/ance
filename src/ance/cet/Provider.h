#ifndef PROVIDER_H
#define PROVIDER_H

#include "ance/core/Identifier.h"
#include "ance/utility/Owners.h"
#include "ance/utility/Containers.h"
#include "ance/utility/Optional.h"

namespace ance::bbt
{
    class Function;
}

namespace ance::cet
{
    /// Provides entities to use during resolution.
    class Provider
    {
    public:
        Provider();
        ~Provider();

        static utility::Owned<Provider> fromList(utility::List<utility::Shared<bbt::Function>>&& functions);

        /// Provides a function for the given identifier, if it exists.
        [[nodiscard]] utility::Optional<utility::Shared<bbt::Function>> provide(core::Identifier const& identifier);

    private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
