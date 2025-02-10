#ifndef ANCE_RET_RESOLVER_H
#define ANCE_RET_RESOLVER_H

#include "ance/core/Reporter.h"
#include "ance/utility/Owners.h"

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
        Resolver();
        ~Resolver();

        /**
       * Resolve a statement.
       * @param statement The statement to resolve.
       * @return The resolved statement.
       */
        utility::Owned<Statement> resolve(est::Statement const& statement);

        // todo: should also have a method addFunction(std::string const& name, std::function<void()> const& function)

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
