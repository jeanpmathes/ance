#ifndef ANCE_EST_EXPANDER_H
#define ANCE_EST_EXPANDER_H

#include <filesystem>

#include "ance/utility/Owners.h"
#include "ance/core/Reporter.h"
#include "ance/core/Context.h"

namespace ance::sources
{
    class SourceTree;
}

namespace ance::est
{
    struct Statement;

    /// Expands ASTs into ESTs.
    class Expander
    {
      public:
        Expander(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context);
        ~Expander();

        /// Expand a statement in a file, removing syntactic sugar.
        /// \param file The path to the file to expand.
        /// \param out The output stream to report to.
        /// \return The expanded statement.
        utility::Optional<utility::Owned<Statement>> expand(std::filesystem::path const& file, std::ostream& out);

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
