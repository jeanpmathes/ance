#ifndef ANCE_RET_RESOLVER_H
#define ANCE_RET_RESOLVER_H

#include "ance/core/Reporter.h"
#include "ance/utility/Owners.h"

namespace ance::core
{
    class Scope;
    class Function;
}

namespace ance::est
{
    struct Statement;
}

namespace ance::ret
{
    struct Statement;

    /// Resolves ESTs into RETs.
    class Resolver
    {
      public:
        explicit Resolver(core::Reporter& reporter);
        ~Resolver();

        /// Register a function.
        /// \param function The function to register.
        void add(core::Function const& function);

        /// Resolve a statement.
        /// \param statement The statement to resolve.
        /// \return The resolved statement.
        utility::Owned<Statement> resolve(est::Statement const& statement);

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
