#ifndef ANCE_EST_EXPANDER_H
#define ANCE_EST_EXPANDER_H

#include "ance/utility/Owners.h"
#include "ance/core/Reporter.h"

namespace ance::ast
{
    struct Statement;
}

namespace ance::est
{
    struct Statement;

    /// Expands ASTs into ESTs.
    class Expander
    {
      public:
        explicit Expander(core::Reporter& reporter);
        ~Expander();

        /// Expand a statement, removing syntactic sugar.
        /// \param statement The statement to expand.
        /// \return The expanded statement.
        utility::Owned<Statement> expand(ast::Statement const& statement);

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
