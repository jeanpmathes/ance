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
     * Resolves ESTs into RETs while performing semantic analysis.
     */
    class Resolver
    {
      public:
        Resolver();
        ~Resolver();

        // todo: do all the intermediate steps for the minimal grammar
        // todo: do the resolver like the expander - the resolver has to do nothing for now essentially
        // todo: when arrived at the compiler, add empty visitor there
        // todo: in the runner, simply print the identifiers
        // todo: then add the function registration to resolver and an intrinsic class instead of std::function
        // todo: then add an extended grammar with all statements and expressions

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
