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
    struct Declaration;
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

        /// Expand a piece of core code containing a single declaration, removing syntactic sugar.
        /// \param code The code to expand.
        /// \param id An identifier of the declaration.
        /// \return The expanded declaration.
        utility::Optional<utility::Owned<Declaration>> expandDeclaration(std::string const& code, std::string const& id);

      private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
