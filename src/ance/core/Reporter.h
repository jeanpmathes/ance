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

        /// Report an informational message.
        /// \param message The message describing the information.
        /// \param location The location in the source code where the information is relevant.
        void info(std::string const& message, Location const& location);

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

        /// Emit all messages, clear them and return whether compilation should fail.
        bool checkForFail(sources::SourceTree& source_tree, std::ostream& out);

        /// Get the number of reported errors.
        /// \return The error count.
        [[nodiscard]] size_t errorCount() const;

        /// Get the number of reported warnings.
        /// \return The warning count.
        [[nodiscard]] size_t warningCount() const;

        /// Print a message to the given output stream with the given prefix.
        /// It uses the formatting of the reporter.
        /// \param out The output stream to print to.
        /// \param prefix The prefix to use, e.g. "info", "command",
        /// \param message The message to print.
        static void print(std::ostream& out, std::string const& prefix, std::string const& message);

    private:
        struct Implementation;
        utility::Owned<Implementation> implementation_;
    };
}

#endif
