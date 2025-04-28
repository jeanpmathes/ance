#ifndef ANCE_CORE_REPORTER_H
#define ANCE_CORE_REPORTER_H

#include <string>

#include "ance/utility/Owners.h"

#include "Location.h"

namespace ance::sources
{
    class SourceTree;
}

namespace ance::core
{
    /// Serves to report errors and warnings.
    class Reporter
    {
    public:
        Reporter();
        ~Reporter();

        /// Report a warning.
        /// \param message The message describing the warning.
        /// \param location The location in the source code where the warning occurred.
        void warning(std::string const& message, Location const& location);

        /// Report an error. The error will prevent successful compilation.
        /// \param message The message describing the error.
        /// \param location The location in the source code where the error occurred.
        void error(std::string const& message, Location const& location);

        /// Emit all reported messages.
        /// \param source_tree The source tree to use for source locations.
        /// \param out The stream to emit the messages to.
        void emit(sources::SourceTree& source_tree, std::ostream& out) const;

        /// Clear all reported messages.
        void clear();

        /// Get the number of reported errors.
        /// \return The error count.
        [[nodiscard]] size_t errorCount() const;

        /// Get the number of reported warnings.
        /// \return The warning count.
        [[nodiscard]] size_t warningCount() const;

    private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
