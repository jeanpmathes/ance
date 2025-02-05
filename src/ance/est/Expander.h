#ifndef ANCE_EST_EXPANDER_H
#define ANCE_EST_EXPANDER_H

#include "ance/utility/Owners.h"

namespace ance::ast
{
    struct Statement;
}

namespace ance::est
{
    struct Statement;

    /**
     * Expands ASTs into ESTs.
     */
    class Expander
    {
      public:
        Expander();
        ~Expander();

        /**
         * Expand a statement, removing syntactic sugar.
         * @param statement The statement to expand.
         * @return The expanded statement.
         */
        utility::Owned<Statement> expand(ast::Statement const& statement);

        // todo: do all the intermediate steps for the minimal grammar, starting with the expander
        // todo: when arrived at the compiler, do nothing there
        // todo: in the runner, simply print the identifiers
        // todo: then add the function registration to runner
        // todo: then add an extended grammar with all statements and expressions

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
