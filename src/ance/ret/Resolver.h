#ifndef ANCE_RET_RESOLVER_H
#define ANCE_RET_RESOLVER_H

#include "ance/core/Reporter.h"
#include "ance/utility/Owners.h"

namespace ance::core
{
    struct Intrinsic;
}

namespace ance::est
{
    struct Statement;
}

namespace ance::ret
{
    struct Statement;

    /**
     * Resolves ESTs into RETs.
     */
    class Resolver
    {
      public:
        explicit Resolver(core::Reporter& reporter);
        ~Resolver();

        /**
         * Register an intrinsic.
         * @param intrinsic The intrinsic to register.
         */
        void add(core::Intrinsic const& intrinsic);

        /**
         * Resolve a statement.
         * @param statement The statement to resolve.
         * @return The resolved statement.
         */
        utility::Owned<Statement> resolve(est::Statement const& statement);

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
