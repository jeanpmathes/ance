#ifndef ANCE_CORE_REPORTER_H
#define ANCE_CORE_REPORTER_H

#include <functional>
#include <sstream>
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
        class MessageBuilder
        {
        public:
            MessageBuilder() = delete;

            MessageBuilder(Reporter& reporter, std::string  compiler_location, Location const& location, bool enabled);
            MessageBuilder(MessageBuilder&& other) noexcept;

            MessageBuilder(MessageBuilder const&) = delete;

            MessageBuilder& operator=(MessageBuilder&& other) noexcept;
            MessageBuilder& operator=(MessageBuilder const&) = delete;

            ~MessageBuilder();

            template<typename T>
            MessageBuilder& operator<<(T const& value)
            {
                if (stream_.hasValue()) stream_.value() << value;
                return *this;
            }

        private:
            Reporter*                               reporter_;
            std::string compiler_location_;
            Location                                location_;

            utility::Optional<std::ostringstream> stream_   = std::nullopt;
        };

        Reporter(sources::SourceTree& source_tree, std::ostream& out, bool trace_enabled);
        ~Reporter();

        /// Report a trace message. Trace messages are only output if the reported is configured to do so.
        /// \param message The message describing the trace.
        /// \param compiler_location The location in the compiler where the trace is relevant, e.g. the name of the step.
        /// \param location The location in the source code where the trace is relevant.
        void trace(std::string const& message, std::string const& compiler_location, Location const& location);

        /// Report a trace message. Trace messages are only output if the reported is configured to do so.
        /// \param message_builder A function that builds the message describing the trace. It is only called if the message is actually output, so it can be used to avoid expensive string construction when the trace is not enabled.
        /// \param compiler_location The location in the compiler where the trace is relevant, e.g. the name of the step.
        /// \param location The location in the source code where the trace is relevant.
        void trace(std::function<std::string()> const& message_builder, std::string const& compiler_location, Location const& location);

        /// Start building a trace message. Trace messages are only output if the reported is configured to do so.
        /// \param location The location in the source code where the trace is relevant.
        /// \param compiler_location The location in the compiler where the trace is relevant, e.g. the name of the step.
        /// \return A message builder that can be used to build the message describing the trace. The message is output when the message builder is destroyed.
        MessageBuilder trace(std::string const& compiler_location, Location const& location);

        /// Report an informational message.
        /// \param message The message describing the information.
        /// \param location The location in the source code where the information is relevant.
        void info(std::string const& message, Location const& location);

        /// Start building an informational message.
        /// \param location The location in the source code where the information is relevant.
        /// \return A message builder that can be used to build the message describing the information. The message is output when the message builder is destroyed.
        MessageBuilder info(Location const& location);

        /// Report a warning.
        /// \param message The message describing the warning.
        /// \param location The location in the source code where the warning occurred.
        void warning(std::string const& message, Location const& location);

        /// Start building a warning message.
        /// \param location The location in the source code where the warning occurred.
        /// \return A message builder that can be used to build the message describing the warning. The message is output when the message builder is destroyed.
        MessageBuilder warning(Location const& location);

        /// Report an error. The error will prevent successful compilation.
        /// \param message The message describing the error.
        /// \param location The location in the source code where the error occurred.
        void error(std::string const& message, Location const& location);

        /// Start building an error message. The error will prevent successful compilation.
        /// \param location The location in the source code where the error occurred.
        /// \return A message builder that can be used to build the message describing the error. The message is output when the message builder is destroyed.
        MessageBuilder error(Location const& location);

        /// Clear the state of the reporter.
        void clear(); // todo: check if this is ever used

        /// Report a summary and clear the state.
        void report();

        /// Check whether compilation should fail.
        [[nodiscard]] bool isFailed() const;

        /// Get the number of reported errors.
        /// \return The error count.
        [[nodiscard]] size_t errorCount() const;

        /// Get the number of reported warnings.
        /// \return The warning count.
        [[nodiscard]] size_t warningCount() const;

        /// Check whether trace messages are enabled.
        /// \return True if trace messages are enabled, false otherwise.
        [[nodiscard]] bool isTraceEnabled() const;

        /// Print a message to the given output stream.
        /// It uses the formatting of the reporter.
        /// \param out The output stream to print to.
        /// \param message The message to print.
        static void print(std::ostream& out, std::string const& message);

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
