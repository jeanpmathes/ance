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
    struct File;
    struct Statement;

    /// Expands ASTs into ESTs.
    class Expander
    {
      public:
        Expander(sources::SourceTree& source_tree, core::Reporter& reporter, core::Context& context);
        ~Expander();

        /// Expand an ordered scope in a file, removing syntactic sugar.
        /// \param file The path to the file to expand.
        /// \return The expanded statement.
        utility::Optional<utility::Owned<Statement>> expandOrderedFile(std::filesystem::path const& file);

        /// Expand an unordered scope in a file, removing syntactic sugar.
        /// \param file The path to the file to expand.
        /// \return The expanded file.
        utility::Optional<utility::Owned<File>> expandUnorderedFile(std::filesystem::path const& file);

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
